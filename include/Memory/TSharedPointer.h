#pragma once

namespace EngineUtilities {

	/**
	 * @brief Clase que facilita la gestión compartida de memoria para objetos.
	 *
	 * Imagina que tienes un objeto en memoria que deseas compartir con otros elementos
	 * de tu programa sin duplicarlo. TSharedPointer gestiona este objeto y se asegura de
	 * que, cuando ya no se necesite, la memoria se libere correctamente. También lleva un
	 * conteo de cuántos TSharedPointer están compartiendo el mismo objeto.
	 */
	template<typename T>
	class TSharedPointer
	{
	public:
		/**
		 * @brief Constructor vacío.
		 *
		 * Este constructor crea un TSharedPointer que no apunta a nada todavía.
		 */
		TSharedPointer() : ptr(nullptr), refCount(nullptr) {}

		/**
		 * @brief Constructor a partir de un puntero normal.
		 *
		 * Aquí, le pasas un puntero crudo (un puntero que no tiene ningún control adicional)
		 * y el TSharedPointer empieza a gestionarlo automáticamente.
		 *
		 * @param rawPtr Puntero al objeto que quieres que sea gestionado.
		 */
		explicit TSharedPointer(T* rawPtr) : ptr(rawPtr), refCount(new int(1)) {}

		/**
		 * @brief Constructor que toma tanto un puntero como un conteo de referencias.
		 *
		 * En este caso, usas un puntero y un conteo de referencias que ya existían previamente.
		 * Esto es útil si deseas crear una nueva instancia de TSharedPointer que comparta un
		 * objeto que ya estaba siendo gestionado por otro TSharedPointer.
		 *
		 * @param rawPtr Puntero al objeto.
		 * @param existingRefCount Puntero al contador de referencias ya existente.
		 */
		TSharedPointer(T* rawPtr, int* existingRefCount) : ptr(rawPtr), refCount(existingRefCount)
		{
			if (refCount)
			{
				++(*refCount); // Aumenta el contador si ya existe.
			}
		}

		/**
		 * @brief Constructor de copia.
		 *
		 * Cuando copias un TSharedPointer, no se duplica el objeto en sí, solo se copia
		 * la referencia al objeto, y se incrementa el conteo de referencias.
		 *
		 * @param other Otro TSharedPointer que gestiona el mismo tipo de objeto.
		 */
		TSharedPointer(const TSharedPointer<T>& other) : ptr(other.ptr), refCount(other.refCount)
		{
			if (refCount)
			{
				++(*refCount); // El contador de referencias aumenta.
			}
		}

		/**
		 * @brief Constructor de movimiento.
		 *
		 * Aquí transfieres la propiedad del puntero y el conteo de referencias a este nuevo
		 * objeto, y el TSharedPointer original queda vacío.
		 *
		 * @param other Otro TSharedPointer que será vaciado.
		 */
		TSharedPointer(TSharedPointer<T>&& other) noexcept : ptr(other.ptr), refCount(other.refCount)
		{
			// Vaciamos el otro TSharedPointer
			other.ptr = nullptr;
			other.refCount = nullptr;
		}

		/**
		 * @brief Asignación por copia.
		 *
		 * Aquí liberas el objeto actual (si lo hay) y asignas un nuevo TSharedPointer, aumentando
		 * el conteo de referencias de ese objeto.
		 *
		 * @param other Otro TSharedPointer del mismo tipo.
		 * @return Referencia al propio TSharedPointer.
		 */
		TSharedPointer<T>& operator=(const TSharedPointer<T>& other)
		{
			if (this != &other)
			{
				// Primero liberamos lo que esté gestionado actualmente.
				if (refCount && --(*refCount) == 0)
				{
					delete ptr;
					delete refCount;
				}
				// Ahora copiamos el nuevo puntero y su conteo de referencias.
				ptr = other.ptr;
				refCount = other.refCount;
				if (refCount)
				{
					++(*refCount); // Incrementa el contador de referencias.
				}
			}
			return *this;
		}

		/**
		 * @brief Asignación por movimiento.
		 *
		 * Similar a la asignación por copia, pero aquí estamos tomando posesión de los datos
		 * y dejando el TSharedPointer original vacío.
		 *
		 * @param other Otro TSharedPointer que será vaciado.
		 * @return Referencia al propio TSharedPointer.
		 */
		TSharedPointer<T>& operator=(TSharedPointer<T>&& other) noexcept
		{
			if (this != &other)
			{
				// Liberamos el puntero actual antes de hacer el cambio.
				if (refCount && --(*refCount) == 0)
				{
					delete ptr;
					delete refCount;
				}
				// Transferimos los datos del otro TSharedPointer.
				ptr = other.ptr;
				refCount = other.refCount;
				other.ptr = nullptr;
				other.refCount = nullptr;
			}
			return *this;
		}

		/**
		 * @brief Destructor.
		 *
		 * Cuando ya no queda ninguna instancia de TSharedPointer gestionando el objeto,
		 * se libera automáticamente la memoria.
		 */
		~TSharedPointer()
		{
			if (refCount && --(*refCount) == 0)
			{
				delete ptr;
				delete refCount;
			}
		}

		// Resto de la implementación similar...

	};

	// Función para crear un TSharedPointer de manera más sencilla.
	template<typename T, typename... Args>
	TSharedPointer<T> MakeShared(Args... args)
	{
		return TSharedPointer<T>(new T(args...));
	}
}
