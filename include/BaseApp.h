#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"

class BaseApp {
public:
    /**
     * @brief Constructor por defecto de `BaseApp`.
     *
     * Inicializa una instancia básica de la aplicación. No se realizan configuraciones en este constructor.
     */
    BaseApp() = default;

    /**
     * @brief Destructor por defecto de `BaseApp`.
     *
     * No realiza ninguna acción específica ya que los punteros inteligentes y otros mecanismos se encargan de la limpieza.
     */
    ~BaseApp() = default;

    /**
     * @brief Ejecuta la aplicación.
     *
     * Esta función es llamada desde `main` y contiene el bucle principal de la aplicación.
     * Se encarga de la actualización de estados, renderizado y manejo de eventos.
     *
     * @return El valor de retorno es el código de salida de la aplicación.
     */
    int run();

    /**
     * @brief Inicializa los componentes de la aplicación.
     *
     * Realiza configuraciones iniciales, como la creación de la ventana, actores y otros recursos necesarios para ejecutar la aplicación.
     *
     * @return `true` si la inicialización es exitosa, `false` si ocurre algún fallo.
     */
    bool initialize();

    /**
     * @brief Actualiza el estado de la aplicación en cada frame.
     *
     * Esta función se llama una vez por frame. Maneja la lógica de actualización, incluyendo el movimiento de actores y la actualización del estado general de la aplicación.
     */
    void update();

    /**
     * @brief Renderiza el contenido de la aplicación.
     *
     * Se encarga de dibujar todos los elementos en la ventana, como los actores, formas y otros gráficos. Esta función se llama una vez por frame después de la actualización.
     */
    void render();

    /**
     * @brief Limpia los recursos utilizados por la aplicación.
     *
     * Libera memoria y destruye los objetos creados, asegurando que la aplicación se cierre de manera limpia y que no haya fugas de memoria.
     */
    void cleanup();

    /**
     * @brief Actualiza el movimiento del círculo.
     *
     * Esta función maneja el movimiento de un actor circular basado en el `deltaTime` proporcionado.
     * Puede incluir lógica de navegación o movimiento basado en waypoints.
     *
     * @param deltaTime Tiempo transcurrido desde el último frame, utilizado para asegurar un movimiento suave.
     * @param circle Puntero compartido (`TSharedPointer`) al actor que representa el círculo que se actualizará.
     */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
    sf::Clock clock; ///< Reloj utilizado para medir el tiempo entre frames.
    sf::Time deltaTime; ///< Almacena el tiempo transcurrido desde el último frame.

    Window* m_window; ///< Puntero a la ventana principal de la aplicación.

    EngineUtilities::TSharedPointer<Actor> Triangle; ///< Actor que representa un triángulo en la escena.
    EngineUtilities::TSharedPointer<Actor> Circle; ///< Actor que representa un círculo en la escena.

    // Variables para la actividad de búsqueda de waypoints
    int currentWaypoint = 0; ///< Índice del waypoint actual hacia el que se dirige el actor.

    // Lista de puntos (waypoints) que el actor seguirá en la escena.
    std::vector<sf::Vector2f> waypoints = {
        {100.0f, 100.0f},
        {400.0f, 100.0f},
        {400.0f, 400.0f},
        {100.0f, 400.0f}
    };
};
