#pragma once

namespace EngineUtilities {

	/**
	 * @brief Clase que facilita la gesti�n compartida de memoria para objetos.
	 *
	 * Imagina que tienes un objeto en memoria que deseas compartir con otros elementos
	 * de tu programa sin duplicarlo. TSharedPointer gestiona este objeto y se asegura de
	 * que, cuando ya no se necesite, la memoria se libere correctamente. Tambi�n lleva un
	 * conteo de cu�ntos TSharedPointer est�n compartiendo el mismo objeto.
	 */
	template<typename T>
	class TSharedPointer
	{
	public:
		/**
		 * @brief Constructor vac�o.
		 *
		 * Este constructor crea un TSharedPointer que no apunta a nada todav�a.
		 */
		TSharedPointer() : ptr(nullptr), refCount(nullptr) {}

		/**
		 * @brief Constructor a partir de un puntero normal.
		 *
		 * Aqu�, le pasas un puntero crudo (un puntero que no tiene ning�n control adicional)
		 * y el TSharedPointer empieza a gestionarlo autom�ticamente.
		 *
		 * @param rawPtr Puntero al objeto que quieres que sea gestionado.
		 */
		explicit TSharedPointer(T* rawPtr) : ptr(rawPtr), refCount(new int(1)) {}

		/**
		 * @brief Constructor que toma tanto un puntero como un conteo de referencias.
		 *
		 * En este caso, usas un puntero y un conteo de referencias que ya exist�an previamente.
		 * Esto es �til si deseas crear una nueva instancia de TSharedPointer que comparta un
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
		 * Cuando copias un TSharedPointer, no se duplica el objeto en s�, solo se copia
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
		 * Aqu� transfieres la propiedad del puntero y el conteo de referencias a este nuevo
		 * objeto, y el TSharedPointer original queda vac�o.
		 *
		 * @param other Otro TSharedPointer que ser� vaciado.
		 */
		TSharedPointer(TSharedPointer<T>&& other) noexcept : ptr(other.ptr), refCount(other.refCount)
		{
			// Vaciamos el otro TSharedPointer
			other.ptr = nullptr;
			other.refCount = nullptr;
		}

		/**
		 * @brief Asignaci�n por copia.
		 *
		 * Aqu� liberas el objeto actual (si lo hay) y asignas un nuevo TSharedPointer, aumentando
		 * el conteo de referencias de ese objeto.
		 *
		 * @param other Otro TSharedPointer del mismo tipo.
		 * @return Referencia al propio TSharedPointer.
		 */
		TSharedPointer<T>& operator=(const TSharedPointer<T>& other)
		{
			if (this != &other)
			{
				// Primero liberamos lo que est� gestionado actualmente.
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
		 * @brief Asignaci�n por movimiento.
		 *
		 * Similar a la asignaci�n por copia, pero aqu� estamos tomando posesi�n de los datos
		 * y dejando el TSharedPointer original vac�o.
		 *
		 * @param other Otro TSharedPointer que ser� vaciado.
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
		 * se libera autom�ticamente la memoria.
		 */
		~TSharedPointer()
		{
			if (refCount && --(*refCount) == 0)
			{
				delete ptr;
				delete refCount;
			}
		}

		// Resto de la implementaci�n similar...

	};

	// Funci�n para crear un TSharedPointer de manera m�s sencilla.
	template<typename T, typename... Args>
	TSharedPointer<T> MakeShared(Args... args)
	{
		return TSharedPointer<T>(new T(args...));
	}
}
