#pragma once

class MemoryAddress
{
public:

	std::uintptr_t GetPtr()
	{
		return ptr;
	}

	MemoryAddress() = default;
	MemoryAddress(std::uintptr_t ptr) : ptr(ptr) {}
	MemoryAddress(void* ptr) : ptr(std::uintptr_t(ptr)) {}

	void operator=(std::uintptr_t newptr) { ptr = newptr; }
	void operator=(void* newptr) { ptr = std::uintptr_t(newptr); }

	operator std::uintptr_t() const
	{
		return ptr;
	}

	operator void* ()
	{
		return reinterpret_cast<void*>(ptr);
	}

	template<typename T>
	operator T* ()
	{
		return reinterpret_cast<T*>(ptr);
	}

	operator bool()
	{
		return ptr != NULL;
	}

	bool operator!=(const MemoryAddress& addr) const
	{
		return ptr != addr.ptr;
	}

	bool operator==(const MemoryAddress& addr) const
	{
		return ptr == addr.ptr;
	}

	bool operator==(std::uintptr_t addr) const
	{
		return ptr == addr;
	}

	template<typename T>
	T Cast()
	{
		return reinterpret_cast<T>(ptr);
	}

	template<class T>
	T GetValue()
	{
		return *reinterpret_cast<T*>(ptr);
	}

	template<class T>
	T& GetValueRef()
	{
		return *reinterpret_cast<T*>(ptr);
	}

	MemoryAddress Offset(std::ptrdiff_t offset)
	{
		return MemoryAddress(ptr + offset);
	}

	MemoryAddress OffsetSelf(std::ptrdiff_t offset)
	{
		ptr += offset;
		return *this;
	}

	MemoryAddress Deref(int deref = 1)
	{
		std::uintptr_t reference = ptr;

		while (deref--)
		{
			if (reference)
				reference = *reinterpret_cast<std::uintptr_t*>(reference);
		}

		return MemoryAddress(reference);
	}

	MemoryAddress DerefSelf(int deref = 1)
	{
		while (deref--)
		{
			if (ptr)
				ptr = *reinterpret_cast<std::uintptr_t*>(ptr);
		}

		return *this;
	}

	template<std::size_t SIZE>
	bool CheckOpCodes(const uint8_t(&opcodeArray)[SIZE])
	{
		std::uintptr_t reference = ptr; // Create pointer reference.

		// Loop forward in the ptr class member.
		for (size_t i = 0; i < SIZE; i++, reference++)
		{
			auto byteAtCurrentAddress = *reinterpret_cast<std::uint8_t*>(reference); // Get byte at current address.

			if (byteAtCurrentAddress != opcodeArray[i]) // If byte at ptr doesn't equal in the byte array return false.
				return false;
		}

		return true;
	}

	template<std::size_t SIZE>
	void Patch(const uint8_t(&opcodes)[SIZE])
	{
		DWORD oldProt = NULL;

		size_t dwSize = SIZE;
		VirtualProtect((void*)ptr, dwSize, PAGE_EXECUTE_READWRITE, &oldProt); // Patch page to be able to read and write to it.

		for (int i = 0; i < SIZE; i++)
		{
			*(std::uint8_t*)(ptr + i) = opcodes[i]; // Write opcodes to address.
		}

		dwSize = SIZE;
		VirtualProtect((void*)ptr, dwSize, oldProt, &oldProt); // Restore protection.
	}

	template<typename T>
	void Patch(const T& data)
	{
		DWORD oldProt = NULL;

		VirtualProtect((void*)ptr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProt); // Patch page to be able to read and write to it.
		*(T*)(ptr) = data; // Write opcode to address.
		VirtualProtect((void*)ptr, sizeof(T), oldProt, &oldProt); // Restore protection.
	}

	void PatchByte(uint8_t byte)
	{
		return Patch<uint8_t>(byte);
	}

	void Memset(uint8_t value, size_t num)
	{
		DWORD oldProt = NULL;
		VirtualProtect((void*)ptr, num, PAGE_EXECUTE_READWRITE, &oldProt); // Patch page to be able to read and write to it.
		memset((void*)ptr, value, num);
		VirtualProtect((void*)ptr, num, oldProt, &oldProt); // Restore protection.
	}

private:
	std::uintptr_t ptr = 0;
};
