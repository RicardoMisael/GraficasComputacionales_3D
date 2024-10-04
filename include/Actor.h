#pragma once
#include "TSharedPointer.h"

namespace EngineUtilities {

    /**
     * @brief Clase diseñada para observar objetos administrados por `TSharedPointer` sin interferir en la cantidad de referencias.
     *
     * `TWeakPointer` permite tener una referencia no intrusiva a un objeto manejado por `TSharedPointer`.
     * Esto significa que puedes ver el objeto si aún existe, pero no evitarás que sea destruido cuando
     * todas las referencias principales hayan sido liberadas. Si el objeto ha sido eliminado, este puntero
     * dejará de ser válido.
     */
    template<typename T>
    class TWeakPointer
    {
    public:
        /**
         * @brief Inicialización por defecto.
         *
         * Crea un `TWeakPointer` que no observa ningún objeto, con punteros nulos a la referencia del objeto y su contador.
         */
        TWeakPointer() : ptr(nullptr), refCount(nullptr) {}

        /**
         * @brief Crea un `TWeakPointer` basado en un `TSharedPointer`.
         *
         * Usa un `TSharedPointer` existente para crear un `TWeakPointer`, permitiendo que observes el objeto sin aumentar el recuento de referencias.
         *
         * @param sharedPtr El `TSharedPointer` del cual se deriva la observación.
         */
        TWeakPointer(const TSharedPointer<T>& sharedPtr)
            : ptr(sharedPtr.ptr), refCount(sharedPtr.refCount) {}

        /**
         * @brief Convierte el `TWeakPointer` en un `TSharedPointer`.
         *
         * Este método intenta transformar el `TWeakPointer` en un `TSharedPointer`, pero solo si el objeto original aún sigue existiendo.
         * Si el objeto ha sido destruido, el `TWeakPointer` no puede convertirse en un `TSharedPointer` válido.
         *
         * @return Un `TSharedPointer` válido si el objeto todavía existe, de lo contrario, un `TSharedPointer` nulo.
         */
        TSharedPointer<T> lock() const
        {
            // Si el contador de referencias es válido y mayor que cero, el objeto aún existe.
            if (refCount && *refCount > 0)
            {
                return TSharedPointer<T>(ptr, refCount);  // Crea un nuevo `TSharedPointer` apuntando al mismo objeto.
            }
            return TSharedPointer<T>();  // Retorna un puntero nulo si el objeto ha sido destruido.
        }

        // Hacer que `TSharedPointer` sea amigo para que tenga acceso a los datos privados.
        template<typename U>
        friend class TSharedPointer;

    private:
        T* ptr;       ///< Referencia al objeto observado, pero no gestionado por este puntero.
        int* refCount; ///< Puntero al contador de referencias del `TSharedPointer` asociado.
    };

}
