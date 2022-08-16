#include "example.h"

#include <cstdlib>

#include <ClassDescription.h>


// Class Description needs to be registered before any functions
// Never put any Register Macros inside a header, otherwise the classes/functions will be registered multiple times.
INF_REGISTER_CLASS(PBNI_Example, L"u_pbni_example");
// Basically every string you use with PowerBuilder should be a wide string, so put L's infront of everything


// All Function Registrations need to be in the same file as the Class Registeristration
INF_REGISTER_FUNC(of_basic_func);
void PBNI_Example::of_basic_func()
{
	MessageBoxW(NULL, L"A PBNI Function got called", L"PBNI Msg", MB_OK);
}

// INF_REGISTER_FUNC needs to have the same amount of argument names as the registered function
// INF_REGISTER_FUNC will automatically deduce argument and return types
INF_REGISTER_FUNC(of_args_ref_return, L"aui_count", L"all_by_ref");
Inf::PBBoolean PBNI_Example::of_args_ref_return(Inf::PBUint aui_count, Inf::PBLongLong& all_by_ref)
{
	// When the function returns the PowerBuilder longlong will be set to all_by_ref
	all_by_ref = aui_count;

	// Automatic cast from bool to Inf::PBBoolean
	return false;
}


INF_REGISTER_FUNC(of_dates, L"ad_date", L"at_time");
Inf::PBDateTime PBNI_Example::of_dates(Inf::PBDate& ad_date, Inf::PBTime at_time)
{
	// PB[Date][Time] Are just small wrappers, if you want to do actuall calculations, use boost::gregorian
	auto [year, month, day] = ad_date.GetDate();
	auto [hour, minute, second] = at_time.GetTime();


	// If you pass DateTimes as reference you need to do
	ad_date.SetDate(2201, 10, 28);

	// You need to pass m_Session when creating complex types
	Inf::PBDateTime dt(m_Session, year, month, day, hour, minute, second);

	return dt;
}


INF_REGISTER_FUNC(of_strings, L"as_str");
Inf::PBString PBNI_Example::of_strings(Inf::PBString as_str)
{
	// This will convert PowerBuilders utf-16 to Ansi using Windows API
	std::string ansi_str = as_str.GetString();
	// Creates copy of wstring
	std::wstring unicode_str = as_str.GetWString();

	//Incase you use String as reference you need to do
	as_str.SetString(ansi_str);

	// Again conversion to utf-16
	return Inf::PBString(m_Session, ansi_str + ", received from C++");
}


INF_REGISTER_FUNC(of_blobs, L"abl_blob");
Inf::PBBlob PBNI_Example::of_blobs(Inf::PBBlob& abl_blob)
{
	// PBBlob is just a wrapper, GetData returns a pointer to the actual data
	for (pbbyte* byte = abl_blob.GetData(), *end = abl_blob.GetData() + abl_blob.Size(); byte < end; byte++)
	{
		// This will write to the reference
		*byte |= 0b01010101;
	}

	std::vector<pbbyte> cpp_style_blob = { 10, 230, 77 };

	// This creates a copy of the vector in PowerBuilder memory
	return Inf::PBBlob(m_Session, cpp_style_blob.data(), cpp_style_blob.size());
}


INF_REGISTER_FUNC(of_objects, L"u_obj");
Inf::PBObject<L"u_pbni_example"> PBNI_Example::of_objects(Inf::PBObject<L"u_pbni_example"> u_obj)
{
	if (!u_obj.IsNull())
	{
		// Passing (m_Session, 0) wil create a null object with all complex types (except dec)
		Inf::PBObject<L"u_pbni_example"> null_obj(m_Session, 0);

		// You can invoke methods, just need to provide the Return Type
		u_obj.Invoke<Inf::PBObject<L"u_pbni_example">>(L"of_objects", PBRT_FUNCTION, null_obj);

		// If you want to invoke a method with an any field, you need to know the function signature
		// check out pbsig170 in PowerBuilder docs
		// if you dont care about return type, you dont have to provide a return type here, because it doesnt have to find the signature
		u_obj.InvokeSig(L"of_any_func", PBRT_FUNCTION, L"IA", null_obj);
	}

	// Setting and getting fields
	Inf::PBInt x = u_obj.GetField<Inf::PBInt>(L"some_field");
	x += 10;
	u_obj.SetField(L"other_field", x);


	u_obj.GetArrayField<Inf::PBInt>(L"arraysss");
	u_obj.GetObjectField<L"u_other_type">(L"subclass?");
	u_obj.GetObjectField<L"u_other_type.st_sub_type", pbgroup_structure>(L"struct");

	return Inf::PBObject<L"u_pbni_example">(m_Session);
}


INF_REGISTER_FUNC(of_arrays, L"u_obj");
void PBNI_Example::of_arrays(Inf::PBArray<Inf::PBInt> aa_arr)
{
	// Unbounded array start at 1, go up infinetly
	// Gets error when out of bounds
	if (10 <= aa_arr.Size())
	{
		Inf::PBInt x = aa_arr.Get(10);
	}

	// Sets will always be okay
	aa_arr.Set(10468442, 1337);


	// 2D Bounded Array
	// [1 to 4, 1 to 4]
	Inf::PBArray<Inf::PBStruct<L"st_some_thing">, 4, 4> bounded(m_Session);
	for (int i = 1; i <= 4; i++)
	{
		bounded.Set({ i, i }, bounded.Get({ i, 5 - i }));
	}
	
	// Cant return arrays directly, use structs
	return;
}


INF_REGISTER_FUNC(of_throw, L"u_obj");
void PBNI_Example::of_throw(Inf::PBString as_err_msg)
{
	if (std::rand() % 64 < 16)
		// This will throw a Powerbuilder exception, which you need to catch in PB
		throw Inf::PBNI_Exception({ 
			{ L"Error", L"Everything worked as expected!" },
			{ L"Description", L"This error was intentionally thrown" }
		});
}
