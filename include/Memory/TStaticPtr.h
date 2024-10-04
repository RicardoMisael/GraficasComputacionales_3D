#pragma once
namespace EngineUtilities {
    /**
     * @brief Clase TStaticPtr para manejo de un puntero est�tico.
     *
     * La clase TStaticPtr gestiona un �nico objeto est�tico y proporciona m�todos
     * para acceder al objeto, verificar si el puntero es nulo y realizar operaciones
     * b�sicas de manejo de memoria.
     *
     * @tparam T Tipo de dato que se almacenar� como puntero est�tico.
     */
    template<typename T>
    class TStaticPtr
    {
    public:
        /**
         * @brief Constructor por defecto.
         *
         * Inicializa el puntero est�tico como nullptr.
         */
        TStaticPtr() = default;

        /**
         * @brief Constructor que toma un puntero crudo.
         *
         * @param rawPtr Puntero crudo al objeto que se gestionar� est�ticamente.
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
         * Libera la memoria del objeto gestionado si es la �ltima instancia.
         */
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;  ///< Libera la memoria del objeto gestionado.
                instance = nullptr; ///< Establece el puntero est�tico como nullptr.
            }
        }

        /**
         * @brief Obtener el puntero crudo gestionado.
         *
         * @return Puntero crudo al objeto gestionado est�ticamente.
         */
        static T* get()
        {
            return instance;
        }

        /**
         * @brief Verificar si el puntero est�tico es nulo.
         *
         * @return true si el puntero est�tico es nullptr, false en caso contrario.
         */
        static bool isNull()
        {
            return instance == nullptr;
        }

        /**
         * @brief Reiniciar el puntero est�tico con un nuevo objeto.
         *
         * Libera la memoria del objeto actual (si existe) y gestiona el nuevo puntero crudo proporcionado.
         *
         * @param rawPtr Puntero crudo al nuevo objeto que se gestionar�, por defecto nullptr.
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
         * @brief Puntero est�tico que gestiona el �nico objeto de tipo T.
         */
        static T* instance;
    };

    /**
     * @brief Inicializaci�n del puntero est�tico fuera de la clase templada.
     *
     * Se asegura que el puntero est�tico est� inicializado a nullptr antes de su uso.
     */
    template<typename T>
    T* TStaticPtr<T>::instance = nullptr;

    /**
     * @brief Ejemplo de uso de la clase TStaticPtr con la clase MyClass.
     *
     * Este ejemplo demuestra c�mo crear, gestionar y reiniciar un objeto est�tico
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
         * @brief Destructor que indica la eliminaci�n del objeto.
         */
        ~MyClass()
        {
            std::cout << "MyClass destructor: " << value << std::endl;
        }

        /**
         * @brief M�todo para mostrar el valor almacenado en MyClass.
         */
        void display() const
        {
            std::cout << "Value: " << value << std::endl;
        }

    private:
        int value;  ///< Almacena un valor entero para la clase MyClass.
    };

    /**
     * @brief Funci�n principal que muestra el uso de TStaticPtr.
     */
    int main()
    {
        {
            // Crear un TStaticPtr gestionando un nuevo objeto MyClass.
            TStaticPtr<MyClass>::reset(new MyClass(10));
            TStaticPtr<MyClass>::get()->display(); // Output: Value: 10

            // Comprobar si el puntero est�tico no es nulo.
            if (!TStaticPtr<MyClass>::isNull())
            {
                std::cout << "TStaticPtr is not null" << std::endl;
            }

            // Reiniciar el puntero est�tico con un nuevo objeto MyClass.
            TStaticPtr<MyClass>::reset(new MyClass(20));
            TStaticPtr<MyClass>::get()->display(); // Output: Value: 20

            // Reiniciar el puntero est�tico a nullptr.
            TStaticPtr<MyClass>::reset();
            if (TStaticPtr<MyClass>::isNull())
            {
                std::cout << "TStaticPtr is null after reset" << std::endl;
            }
        }

        return 0;
    }
}
