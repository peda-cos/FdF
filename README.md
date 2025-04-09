# Guia Completo de Desenvolvimento do FdF

## Introdução

O FdF (Fil de Fer - "moldura de arame" em francês) é um projeto que transforma arquivos de mapa contendo coordenadas em representações tridimensionais wireframe. Este guia explora a implementação que você desenvolveu, explicando os conceitos fundamentais, algoritmos e detalhes técnicos para quem deseja compreender ou replicar este tipo de visualizador 3D.

## Índice

1. [Estrutura do Projeto](#estrutura-do-projeto)
2. [Biblioteca MLX42](#biblioteca-mlx42)
3. [Estruturas de Dados](#estruturas-de-dados)
4. [Carregamento do Mapa](#carregamento-do-mapa)
5. [Projeção Isométrica](#projeção-isométrica)
6. [Algoritmo de Bresenham](#algoritmo-de-bresenham)
7. [Sistema de Cores](#sistema-de-cores)
8. [Controles da Câmera](#controles-da-câmera)
9. [Gerenciamento de Memória](#gerenciamento-de-memória)
10. [Conclusão](#conclusão)

## Estrutura do Projeto

O projeto está organizado em módulos bem definidos:

```
src/
├── camera_controls.c  - Gerenciamento da câmera e projeção
├── color_processing.c - Processamento e interpolação de cores
├── drawing_helpers.c  - Funções auxiliares para desenho
├── fdf.h              - Definições e estruturas principais
├── input_hooks.c      - Manipulação de entradas do usuário
├── main.c             - Ponto de entrada do programa
├── map_loading.c      - Carregamento do arquivo de mapa
├── map_management.c   - Gerenciamento da estrutura do mapa
├── map_rendering.c    - Renderização do mapa
└── utility_functions.c - Funções utilitárias diversas
```

Cada arquivo tem uma responsabilidade específica, seguindo o princípio de responsabilidade única, o que facilita a manutenção e compreensão do código.

## Biblioteca MLX42

A MLX42 é uma biblioteca gráfica simples usada para renderização. Vamos examinar as principais funções MLX utilizadas:

### Inicialização e Configuração

```c
// Inicializa a biblioteca e cria uma janela
fdf.mlx_instance = mlx_init(WIDTH, HEIGHT, "FdF - peda-cos", true);

// Cria uma nova imagem para desenho
fdf.image = mlx_new_image(fdf.mlx_instance, WIDTH, HEIGHT);

// Coloca a imagem na janela
mlx_image_to_window(fdf.mlx_instance, fdf.image, 0, 0);

// Configura hooks para eventos de entrada
mlx_loop_hook(fdf.mlx_instance, &handle_exit, fdf);

// Inicia o loop principal
mlx_loop(fdf.mlx_instance);

// Finaliza a biblioteca
mlx_terminate(fdf.mlx_instance);
```

### Desenho de Pixels

```c
// Desenha um pixel em coordenadas específicas com uma cor
mlx_put_pixel(image, x, y, color);
```

É importante notar que a MLX42 usa um formato de cor RGBA onde a cor é representada como um número de 32 bits (`uint32_t`).

## Estruturas de Dados

O projeto utiliza várias estruturas para representar os diferentes componentes:

### t_point

```c
typedef struct s_point
{
    int        x;
    int        y;
    int        z;
    uint32_t   color;
} t_point;
```

Esta estrutura representa um ponto no espaço 3D, com coordenadas (x, y, z) e um valor de cor.

### t_map

```c
typedef struct s_map
{
    unsigned int    width;
    unsigned int    height;
    unsigned int    total_points;
    int             min_z;
    int             max_z;
    t_point         *points;
} t_map;
```

Armazena informações sobre o mapa, incluindo dimensões e um array de pontos.

### t_camera

```c
typedef struct s_camera
{
    int             projection_type;
    float           zoom_level;
    double          z_scale_factor;
    int             x_offset;
    int             y_offset;
} t_camera;
```

Gerencia a visualização, incluindo tipo de projeção, zoom e deslocamentos.

### t_fdf

```c
typedef struct s_fdf
{
    t_map           *map;
    t_camera        *camera;
    mlx_t           *mlx_instance;
    mlx_image_t     *image;
} t_fdf;
```

A estrutura principal que conecta todos os componentes.

### t_bresenham

```c
typedef struct s_bresenham
{
    int             delta_x;
    int             delta_y;
    int             step_x;
    int             step_y;
    int             error;
    int             initial_x;
    int             initial_y;
} t_bresenham;
```

Utilizada para implementar o algoritmo de Bresenham para desenho de linhas.

## Carregamento do Mapa

O processo de carregamento do mapa é um dos componentes mais importantes. Vamos analisar como ele foi implementado:

1. **Validação do arquivo**: Verifica se o arquivo tem a extensão `.fdf` e pode ser aberto:

```c
int validate_file_extension(char *file)
{
    int file_descriptor;

    if (!ft_strnstr(file, ".fdf", ft_strlen(file)))
        exit_with_error(ERROR_FILE_EXTENSION);
    file_descriptor = open(file, O_RDONLY);
    if (file_descriptor == -1)
        exit_with_error(ERROR_FILE_OPEN);
    return (file_descriptor);
}
```

2. **Leitura das dimensões**: Lê o arquivo para determinar a largura e altura do mapa:

```c
void load_map(char *file, t_map *map)
{
    // ... (código omitido)
    while (line)
    {
        columns = count_columns(line, ' ');
        free(line);
        if (map->height == 0)
            map->width = columns;
        if (map->width != columns)
            exit_with_error(ERROR_MAP_WIDTH);
        map->height++;
        line = get_next_line(file_descriptor);
    }
    // ... (código omitido)
}
```

3. **Parsing dos pontos**: Converte cada linha do arquivo em pontos 3D:

```c
void parse_line_into_points(char *line, t_map *map, int line_index)
{
    // ... (código omitido)
    while (columns[column_index] && columns[column_index][0] != '\n')
    {
        map->points[start_index + column_index].x = column_index;
        map->points[start_index + column_index].y = line_index;
        map->points[start_index + column_index].z = ft_atoi(columns[column_index]);
        // ... (código omitido)
        map->points[start_index + column_index].color = parse_color(columns[column_index]);
        column_index++;
    }
    // ... (código omitido)
}
```

Esta implementação lê o mapa em duas passagens:
- A primeira para determinar as dimensões
- A segunda para preencher a estrutura de pontos

## Projeção Isométrica

A projeção isométrica é o coração visual do FdF. Esta projeção transforma coordenadas 3D em coordenadas 2D para a tela, mantendo um ângulo igual entre os três eixos principais.

```c
t_point project_point(t_point point, t_fdf *fdf)
{
    int transformed_x;
    int transformed_y;

    transformed_x = point.x;
    transformed_y = point.y;
    
    // Aplica zoom e centraliza
    point.x = point.x * fdf->camera->zoom_level - ((fdf->map->width * fdf->camera->zoom_level) / 2);
    point.y = point.y * fdf->camera->zoom_level - ((fdf->map->height * fdf->camera->zoom_level) / 2);
    point.z = point.z * fdf->camera->zoom_level / fdf->camera->z_scale_factor;
    
    // Aplicação da projeção isométrica
    if (fdf->camera->projection_type == ISOMETRIC)
    {
        transformed_x = (point.x - point.y) * cos(M_PI / 6);
        transformed_y = (-point.z + (point.x + point.y) * sin(M_PI / 6));
    }
    
    // Posicionamento final na tela
    point.x = transformed_x + WIDTH / 2 + fdf->camera->x_offset;
    point.y = transformed_y + HEIGHT / 2 + fdf->camera->y_offset;
    
    return (point);
}
```

Os cálculos podem ser compreendidos da seguinte forma:

1. Primeiro, cada coordenada é multiplicada pelo nível de zoom e centralizada
2. A altura (z) é ajustada pelo fator de escala z
3. As fórmulas da projeção isométrica são aplicadas:
   - `x_iso = (x - y) * cos(30°)`
   - `y_iso = (-z + (x + y) * sin(30°))`
4. Finalmente, o ponto é posicionado na tela, ajustando para o centro da janela e aplicando offsets da câmera

O ângulo de 30° (π/6 radianos) é característico da projeção isométrica, criando um ângulo de 120° entre os eixos projetados.

## Algoritmo de Bresenham

O algoritmo de Bresenham é usado para desenhar linhas eficientemente. A implementação utiliza uma abordagem incremental para determinar quais pixels devem ser coloridos:

```c
void draw_line(t_point start, t_point end, mlx_image_t *image)
{
    t_bresenham bresenham_state;

    initialize_bresenham(start, end, &bresenham_state);
    while (1)
    {
        if (start.x == end.x && start.y == end.y)
            return;
        if (is_within_pixel_boundaries(&start))
            mlx_put_pixel(image, start.x, start.y, 
                interpolate_color(start, end, bresenham_state));
        
        // Lógica principal do Bresenham
        if (2 * bresenham_state.error >= bresenham_state.delta_y)
        {
            if (start.x == end.x)
                return;
            bresenham_state.error += bresenham_state.delta_y;
            start.x += bresenham_state.step_x;
        }
        if (2 * bresenham_state.error <= bresenham_state.delta_x)
        {
            if (start.y == end.y)
                return;
            bresenham_state.error += bresenham_state.delta_x;
            start.y += bresenham_state.step_y;
        }
    }
}
```

A inicialização do estado do Bresenham inclui cálculos importantes:

```c
void initialize_bresenham(t_point start, t_point end, t_bresenham *bresenham_state)
{
    if (start.x < end.x)
        bresenham_state->step_x = 1;
    else
        bresenham_state->step_x = -1;
    
    if (start.y < end.y)
        bresenham_state->step_y = 1;
    else
        bresenham_state->step_y = -1;
    
    bresenham_state->delta_x = abs(end.x - start.x);
    bresenham_state->delta_y = -abs(end.y - start.y);
    bresenham_state->error = bresenham_state->delta_x + bresenham_state->delta_y;
    
    bresenham_state->initial_x = start.x;
    bresenham_state->initial_y = start.y;
}
```

O algoritmo funciona determinando qual pixel escolher ao avançar pela linha, utilizando uma variável de "erro" para rastrear o desvio acumulado. Esta implementação escolhe habilmente o próximo pixel baseando-se no valor de erro atual, evitando cálculos em ponto flutuante caros.

## Sistema de Cores

O sistema de cores lida com a interpretação das cores do arquivo de mapa e a interpolação entre pontos.

### Parsing de Cores

```c
uint32_t parse_color(char *line)
{
    char **tokens;
    uint32_t color_value;

    if (ft_strchr(line, ',') != NULL)
    {
        tokens = ft_split(line, ',');
        if (tokens && tokens[1])
        {
            color_value = ft_atoi_base(tokens[1], "0123456789abcdef");
            color_value = (color_value << 8) | 0xff; // Adiciona canal alpha
        }
        else
            color_value = 0;
        color_value = convert_hex_to_rgba(color_value);
        free_string_array(tokens);
    }
    else
        color_value = convert_hex_to_rgba(0xFFFFFF); // Branco por padrão
    
    return (color_value);
}
```

### Interpolação de Cores

Para criar gradientes suaves entre pontos, uma função de interpolação linear é usada:

```c
uint32_t interpolate_color(t_point start, t_point end, t_bresenham bresenham_state)
{
    int red, green, blue, alpha;
    float ratio;

    if (start.color == end.color)
        return (start.color);
    
    ratio = (float)(start.x - bresenham_state.initial_x) / 
            (float)(end.x - bresenham_state.initial_x);
    
    red = linear_interpolation((start.color >> 24) & 0xFF,
            (end.color >> 24) & 0xFF, ratio);
    green = linear_interpolation((start.color >> 16) & 0xFF,
            (end.color >> 16) & 0xFF, ratio);
    blue = linear_interpolation((start.color >> 8) & 0xFF,
            (end.color >> 8) & 0xFF, ratio);
    alpha = linear_interpolation(start.color & 0xFF, 
            end.color & 0xFF, ratio);
    
    return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
```

A função calcula a proporção atual ao longo da linha e interpola independentemente cada componente de cor (vermelho, verde, azul e alpha).

## Controles da Câmera

Os controles da câmera permitem ao usuário navegar e ajustar a visualização:

```c
void handle_translation(void *param)
{
    t_fdf *fdf;

    fdf = param;
    if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_W))
        fdf->camera->y_offset -= TRANSLATE_STEP;
    else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_S))
        fdf->camera->y_offset += TRANSLATE_STEP;
    else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_A))
        fdf->camera->x_offset -= TRANSLATE_STEP;
    else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_D))
        fdf->camera->x_offset += TRANSLATE_STEP;
    else
        return;
    render_map(fdf);
}

void handle_zoom(void *param)
{
    t_fdf *fdf;

    fdf = param;
    if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_R))
    {
        reset_camera(fdf);
        render_map(fdf);
        return;
    }
    
    // Controles de zoom
    if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_KP_ADD))
        fdf->camera->zoom_level *= 1.1;
    else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_KP_SUBTRACT))
        fdf->camera->zoom_level /= 1.1;
    else if (fdf->camera->zoom_level < 0.01)
        fdf->camera->zoom_level = 0.01;
    
    // Controles de escala Z
    else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_J))
        fdf->camera->z_scale_factor *= 1.1;
    else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_K))
        fdf->camera->z_scale_factor /= 1.1;
    else if (fdf->camera->z_scale_factor < 0.01)
        fdf->camera->z_scale_factor = 0.01;
    else
        return;
        
    render_map(fdf);
}
```

Os controles implementados são:
- **W/A/S/D**: Move a câmera verticalmente e horizontalmente
- **Numpad +/-**: Aumenta/diminui o zoom
- **J/K**: Aumenta/diminui a escala vertical (altura)
- **R**: Reinicia a câmera para configurações padrão
- **ESC**: Fecha o programa

## Gerenciamento de Memória

O projeto gerencia cuidadosamente a memória para evitar vazamentos:

```c
// Liberação da memória do mapa
void free_map(t_map *map)
{
    free(map->points);
    free(map);
}

// Liberação de arrays de strings
void free_string_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// No main.c, liberação de todas as estruturas ao terminar
mlx_terminate(fdf.mlx_instance);
free(fdf.camera);
free_map(fdf.map);
```

## Conclusão

O FdF demonstra vários conceitos fundamentais de computação gráfica:

1. **Transformação de coordenadas**: Conversão de coordenadas 3D para 2D usando projeção isométrica
2. **Rasterização de linhas**: Uso do algoritmo de Bresenham para desenhar linhas eficientemente
3. **Manipulação de cores**: Parsing e interpolação de cores para visualização gradiente
4. **Interatividade**: Sistema de controles para permitir navegação e ajustes na visualização
5. **Gerenciamento de recursos**: Alocação e liberação apropriada de memória

Para expandir este projeto, você poderia considerar:
- Implementar projeções adicionais (perspectiva, oblíqua)
- Adicionar rotação 3D
- Implementar ocultação de faces (não renderizar linhas que estariam atrás de outras)
- Adicionar texturas ou iluminação mais sofisticada

Este guia oferece uma visão detalhada da implementação do FdF, explicando as decisões de design e os algoritmos utilizados.
