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
     * Inicializa una instancia b�sica de la aplicaci�n. No se realizan configuraciones en este constructor.
     */
    BaseApp() = default;

    /**
     * @brief Destructor por defecto de `BaseApp`.
     *
     * No realiza ninguna acci�n espec�fica ya que los punteros inteligentes y otros mecanismos se encargan de la limpieza.
     */
    ~BaseApp() = default;

    /**
     * @brief Ejecuta la aplicaci�n.
     *
     * Esta funci�n es llamada desde `main` y contiene el bucle principal de la aplicaci�n.
     * Se encarga de la actualizaci�n de estados, renderizado y manejo de eventos.
     *
     * @return El valor de retorno es el c�digo de salida de la aplicaci�n.
     */
    int run();

    /**
     * @brief Inicializa los componentes de la aplicaci�n.
     *
     * Realiza configuraciones iniciales, como la creaci�n de la ventana, actores y otros recursos necesarios para ejecutar la aplicaci�n.
     *
     * @return `true` si la inicializaci�n es exitosa, `false` si ocurre alg�n fallo.
     */
    bool initialize();

    /**
     * @brief Actualiza el estado de la aplicaci�n en cada frame.
     *
     * Esta funci�n se llama una vez por frame. Maneja la l�gica de actualizaci�n, incluyendo el movimiento de actores y la actualizaci�n del estado general de la aplicaci�n.
     */
    void update();

    /**
     * @brief Renderiza el contenido de la aplicaci�n.
     *
     * Se encarga de dibujar todos los elementos en la ventana, como los actores, formas y otros gr�ficos. Esta funci�n se llama una vez por frame despu�s de la actualizaci�n.
     */
    void render();

    /**
     * @brief Limpia los recursos utilizados por la aplicaci�n.
     *
     * Libera memoria y destruye los objetos creados, asegurando que la aplicaci�n se cierre de manera limpia y que no haya fugas de memoria.
     */
    void cleanup();

    /**
     * @brief Actualiza el movimiento del c�rculo.
     *
     * Esta funci�n maneja el movimiento de un actor circular basado en el `deltaTime` proporcionado.
     * Puede incluir l�gica de navegaci�n o movimiento basado en waypoints.
     *
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame, utilizado para asegurar un movimiento suave.
     * @param circle Puntero compartido (`TSharedPointer`) al actor que representa el c�rculo que se actualizar�.
     */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
    sf::Clock clock; ///< Reloj utilizado para medir el tiempo entre frames.
    sf::Time deltaTime; ///< Almacena el tiempo transcurrido desde el �ltimo frame.

    Window* m_window; ///< Puntero a la ventana principal de la aplicaci�n.

    EngineUtilities::TSharedPointer<Actor> Triangle; ///< Actor que representa un tri�ngulo en la escena.
    EngineUtilities::TSharedPointer<Actor> Circle; ///< Actor que representa un c�rculo en la escena.

    // Variables para la actividad de b�squeda de waypoints
    int currentWaypoint = 0; ///< �ndice del waypoint actual hacia el que se dirige el actor.

    // Lista de puntos (waypoints) que el actor seguir� en la escena.
    std::vector<sf::Vector2f> waypoints = {
        {100.0f, 100.0f},
        {400.0f, 100.0f},
        {400.0f, 400.0f},
        {100.0f, 400.0f}
    };
};
