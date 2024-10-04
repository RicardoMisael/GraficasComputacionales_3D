#pragma once

namespace EngineUtilities {

    /**
     * @brief Clase que gestiona la memoria de un objeto de forma exclusiva.
     *
     * La clase `TUniquePtr` asegura que solo una instancia de `TUniquePtr` puede
     * gestionar un objeto en cualquier momento dado, garantizando as� que la
     * memoria asociada no ser� compartida. Esta clase es �til cuando se desea
     * un control exclusivo sobre el ciclo de vida de un objeto.
     */
    template<typename T>
    class TUniquePtr
    {
    public:
        /**
         * @brief Constructor por defecto que inicializa el puntero a nullptr.
         *
         * Crea un `TUniquePtr` vac�o que no posee ning�n objeto.
         */
        TUniquePtr() : ptr(nullptr) {}

        /**
         * @brief Constructor que toma un puntero crudo.
         *
         * @param rawPtr Un puntero crudo al objeto que se va a gestionar.
         * Crea un `TUniquePtr` que gestiona el objeto apuntado por `rawPtr`.
         */
        explicit TUniquePtr(T* rawPtr) : ptr(rawPtr) {}

        /**
         * @brief Constructor de movimiento.
         *
         * Toma la propiedad del puntero de otro `TUniquePtr`, transfiriendo
         * la posesi�n del objeto gestionado.
         *
         * @param other Otro `TUniquePtr` desde el cual se transfiere el objeto.
         */
        TUniquePtr(TUniquePtr<T>&& other) noexcept : ptr(other.ptr) {
            other.ptr = nullptr;
        }

        /**
         * @brief Operador de asignaci�n por movimiento.
         *
         * Libera el objeto actual y transfiere la propiedad del puntero del otro
         * `TUniquePtr`. El `TUniquePtr` fuente queda nulo despu�s de la operaci�n.
         *
         * @param other Otro `TUniquePtr` desde el cual se transfiere el objeto.
         * @return Referencia al `TUniquePtr` actual.
         */
        TUniquePtr<T>& operator=(TUniquePtr<T>&& other) noexcept {
            if (this != &other) {
                // Liberar el objeto actual
                delete ptr;

                // Transferir el puntero exclusivo
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        /**
         * @brief Destructor que libera el objeto gestionado.
         *
         * Si el `TUniquePtr` todav�a gestiona un objeto, este ser� eliminado.
         */
        ~TUniquePtr() {
            delete ptr;
        }

        /**
         * @brief Prohibir la copia de `TUniquePtr`.
         *
         * Esto asegura que no se puede copiar un `TUniquePtr`, ya que ser�a peligroso
         * permitir que m�s de un puntero gestione el mismo objeto.
         */
        TUniquePtr(const TUniquePtr<T>&) = delete;

        /**
         * @brief Prohibir la asignaci�n por copia de `TUniquePtr`.
         *
         * Al igual que el constructor de copia, la asignaci�n por copia est� deshabilitada
         * para garantizar que no haya m�ltiples gestores del mismo objeto.
         */
        TUniquePtr<T>& operator=(const TUniquePtr<T>&) = delete;

        /**
         * @brief Operador de desreferenciaci�n.
         *
         * @return Referencia al objeto gestionado.
         */
        T& operator*() const { return *ptr; }

        /**
         * @brief Operador de acceso a miembros.
         *
         * @return Puntero al objeto gestionado.
         */
        T* operator->() const { return ptr; }

        /**
         * @brief Obtener el puntero crudo gestionado.
         *
         * @return El puntero crudo al objeto gestionado por este `TUniquePtr`.
         */
        T* get() const { return ptr; }

        /**
         * @brief Liberar la propiedad del puntero crudo.
         *
         * @return El puntero crudo gestionado, liberando la propiedad del `TUniquePtr`.
         * El `TUniquePtr` queda nulo despu�s de esta operaci�n.
         */
        T* release() {
            T* oldPtr = ptr;
            ptr = nullptr;
            return oldPtr;
        }

        /**
         * @brief Reiniciar el puntero gestionado con un nuevo puntero o nullptr.
         *
         * Libera el objeto gestionado actualmente y asume la gesti�n del nuevo objeto
         * apuntado por `rawPtr`.
         *
         * @param rawPtr Puntero crudo al nuevo objeto que se va a gestionar (por defecto nullptr).
         */
        void reset(T* rawPtr = nullptr) {
            delete ptr;
            ptr = rawPtr;
        }

        /**
         * @brief Verificar si el puntero gestionado es nulo.
         *
         * @return `true` si el puntero gestionado es nulo, `false` en caso contrario.
         */
        bool isNull() const {
            return ptr == nullptr;
        }

    private:
        // Puntero al objeto gestionado.
        T* ptr;
    };

    /**
     * @brief Funci�n de utilidad para crear un `TUniquePtr`.
     *
     * Crea un nuevo objeto de tipo `T` con los argumentos proporcionados y lo
     * gestiona mediante un `TUniquePtr`.
     *
     * @tparam T Tipo del objeto a crear.
     * @tparam Args Tipos de los argumentos necesarios para el constructor del objeto.
     * @param args Argumentos para el constructor del objeto.
     * @return Un nuevo `TUniquePtr` gestionando el objeto creado.
     */
    template<typename T, typename... Args>
    TUniquePtr<T> MakeUnique(Args... args) {
        return TUniquePtr<T>(new T(args...));
    }
}
