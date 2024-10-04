#pragma once
#include "TSharedPointer.h"

namespace EngineUtilities {

    /**
     * @brief Clase que permite observar objetos gestionados por `TSharedPointer` sin aumentar su recuento de referencias.
     *
     * `TWeakPointer` ofrece una forma segura de observar un objeto gestionado por un `TSharedPointer`
     * sin prolongar su vida útil. A diferencia de `TSharedPointer`, no afecta el conteo de referencias.
     * Si el objeto gestionado se ha destruido, el `TWeakPointer` se considerará "expirado" y no proporcionará acceso al objeto.
     */
    template<typename T>
    class TWeakPointer
    {
    public:
        /**
         * @brief Constructor por defecto que inicializa el puntero y el recuento de referencias a nullptr.
         */
        TWeakPointer() : ptr(nullptr), refCount(nullptr) {}

        /**
         * @brief Constructor que crea un `TWeakPointer` a partir de un `TSharedPointer`.
         *
         * Este constructor toma un `TSharedPointer` como argumento y establece
         * el puntero interno y el recuento de referencias para observar el mismo objeto.
         *
         * @param sharedPtr El `TSharedPointer` a partir del cual se observará el objeto.
         */
        TWeakPointer(const TSharedPointer<T>& sharedPtr)
            : ptr(sharedPtr.ptr), refCount(sharedPtr.refCount) {}

        /**
         * @brief Convertir el `TWeakPointer` a un `TSharedPointer`.
         *
         * Este método intenta crear un `TSharedPointer` a partir del `TWeakPointer`.
         * Si el objeto gestionado aún existe (es decir, no ha sido destruido),
         * se devuelve un `TSharedPointer` válido. Si no, se devuelve un `TSharedPointer` nulo.
         *
         * @return Un `TSharedPointer` al objeto gestionado, o nullptr si el objeto ha sido destruido.
         */
        TSharedPointer<T> lock() const
        {
            // Si el objeto aún existe (el recuento de referencias es mayor que cero)
            if (refCount && *refCount > 0)
            {
                return TSharedPointer<T>(ptr, refCount);
            }
            return TSharedPointer<T>();
        }

        // Hacer que `TSharedPointer` sea amigo para que pueda acceder a los miembros privados.
        template<typename U>
        friend class TSharedPointer;

    private:
        T* ptr;       ///< Puntero al objeto observado.
        int* refCount; ///< Puntero al recuento de referencias del `TSharedPointer` original.
    };
}
