#pragma once
namespace EngineUtilities {
    /**
     * @brief Clase TStaticPtr para manejo de un puntero estático.
     *
     * La clase TStaticPtr gestiona un único objeto estático y proporciona métodos
     * para acceder al objeto, verificar si el puntero es nulo y realizar operaciones
     * básicas de manejo de memoria.
     *
     * @tparam T Tipo de dato que se almacenará como puntero estático.
     */
    template<typename T>
    class TStaticPtr
    {
    public:
        /**
         * @brief Constructor por defecto.
         *
         * Inicializa el puntero estático como nullptr.
         */
        TStaticPtr() = default;

        /**
         * @brief Constructor que toma un puntero crudo.
         *
         * @param rawPtr Puntero crudo al objeto que se gestionará estáticamente.
         */
        explicit TStaticPtr(T* rawPtr)
        {
            if (instance != nullptr)
            {
                delete instance;  ///< Elimina el objeto previamente gestionado.
            }
            instance = rawPtr;   ///< Asigna el nuevo puntero crudo al objeto.
        }

        /**
         * @brief Destructor.
         *
         * Libera la memoria del objeto gestionado si es la última instancia.
         */
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;  ///< Libera la memoria del objeto gestionado.
                instance = nullptr; ///< Establece el puntero estático como nullptr.
            }
        }

        /**
         * @brief Obtener el puntero crudo gestionado.
         *
         * @return Puntero crudo al objeto gestionado estáticamente.
         */
        static T* get()
        {
            return instance;
        }

        /**
         * @brief Verificar si el puntero estático es nulo.
         *
         * @return true si el puntero estático es nullptr, false en caso contrario.
         */
        static bool isNull()
        {
            return instance == nullptr;
        }

        /**
         * @brief Reiniciar el puntero estático con un nuevo objeto.
         *
         * Libera la memoria del objeto actual (si existe) y gestiona el nuevo puntero crudo proporcionado.
         *
         * @param rawPtr Puntero crudo al nuevo objeto que se gestionará, por defecto nullptr.
         */
        static void reset(T* rawPtr = nullptr)
        {
            if (instance != nullptr)
            {
                delete instance;  ///< Elimina el objeto previamente gestionado.
            }
            instance = rawPtr;   ///< Asigna el nuevo puntero crudo al objeto.
        }

    private:
        /**
         * @brief Puntero estático que gestiona el único objeto de tipo T.
         */
        static T* instance;
    };

    /**
     * @brief Inicialización del puntero estático fuera de la clase templada.
     *
     * Se asegura que el puntero estático esté inicializado a nullptr antes de su uso.
     */
    template<typename T>
    T* TStaticPtr<T>::instance = nullptr;

    /**
     * @brief Ejemplo de uso de la clase TStaticPtr con la clase MyClass.
     *
     * Este ejemplo demuestra cómo crear, gestionar y reiniciar un objeto estático
     * de tipo MyClass utilizando la clase TStaticPtr.
     */
    class MyClass
    {
    public:
        /**
         * @brief Constructor que inicializa un valor.
         *
         * @param value Valor entero a almacenar en MyClass.
         */
        MyClass(int value) : value(value)
        {
            std::cout << "MyClass constructor: " << value << std::endl;
        }

        /**
         * @brief Destructor que indica la eliminación del objeto.
         */
        ~MyClass()
        {
            std::cout << "MyClass destructor: " << value << std::endl;
        }

        /**
         * @brief Método para mostrar el valor almacenado en MyClass.
         */
        void display() const
        {
            std::cout << "Value: " << value << std::endl;
        }

    private:
        int value;  ///< Almacena un valor entero para la clase MyClass.
    };

    /**
     * @brief Función principal que muestra el uso de TStaticPtr.
     */
    int main()
    {
        {
            // Crear un TStaticPtr gestionando un nuevo objeto MyClass.
            TStaticPtr<MyClass>::reset(new MyClass(10));
            TStaticPtr<MyClass>::get()->display(); // Output: Value: 10

            // Comprobar si el puntero estático no es nulo.
            if (!TStaticPtr<MyClass>::isNull())
            {
                std::cout << "TStaticPtr is not null" << std::endl;
            }

            // Reiniciar el puntero estático con un nuevo objeto MyClass.
            TStaticPtr<MyClass>::reset(new MyClass(20));
            TStaticPtr<MyClass>::get()->display(); // Output: Value: 20

            // Reiniciar el puntero estático a nullptr.
            TStaticPtr<MyClass>::reset();
            if (TStaticPtr<MyClass>::isNull())
            {
                std::cout << "TStaticPtr is null after reset" << std::endl;
            }
        }

        return 0;
    }
}
