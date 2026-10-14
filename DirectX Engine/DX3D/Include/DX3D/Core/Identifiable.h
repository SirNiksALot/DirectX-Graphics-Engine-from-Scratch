#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
/*
Note on how ``using type_id_tag = Class``` works here.
We create an alias for the "Class" type being passed to this macro ( this is called a type alias ) 
we create this type alias becuase later down the line we will use the HasTypeId in our game objects to verify if the getTypeId() method is set.
*/

#define dx3d_typeid(Class)\
public:\
using type_id_tag = Class;\
static size_t GetTypeId(){\
	static const auto id = typeid(Class).hash_code();\
	return id;\
}\
size_t getTypeId() const noexcept override {\
	return  GetTypeId();\
}

namespace dx3d {
	class Identifiable : public Base 
	{
		public:
			explicit Identifiable(const BaseDesc& desc) :
				Base(desc) {

			}

			virtual size_t getTypeId() const noexcept = 0;


	};

	template<typename T>
	concept HasTypeId = std::is_same_v<typename T::type_id_tag, T > ; 
}