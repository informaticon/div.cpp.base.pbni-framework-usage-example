#include "example.h"

#include <cstdlib>

#include "lib.cpp.base.pbni-framework/ClassDescription.h"


INF_REGISTER_CLASS(PBNI_Example, L"u_pbni_ex");

INF_REGISTER_FUNC(of_basic_func);
void PBNI_Example::of_basic_func()
{
	MessageBoxW(NULL, L"A PBNI Function got called", L"PBNI Msg", MB_OK);
}


INF_REGISTER_FUNC(of_args_ref_return, L"aui_count", L"all_by_ref");
Inf::PBBoolean PBNI_Example::of_args_ref_return(Inf::PBUint aui_count, Inf::PBLongLong& all_by_ref)
{
	// When the function returns it will set the PowerBuilder longlong to the ref
	all_by_ref = aui_count;

	// Automatic cast from bool to Inf::PBBoolean
	return false;
}


INF_REGISTER_FUNC(of_dates, L"ad_date", L"at_time");
Inf::PBDateTime PBNI_Example::of_dates(Inf::PBDate ad_date, Inf::PBTime at_time)
{
	// PB[Date][Time] Are just small wrappers, if you want to do actuall calculations, use boost::gregorian
	auto [year, month, day] = ad_date.GetDate();
	auto [hour, minute, second] = at_time.GetTime();


	//Incase you use Datetimes as reference you need to do
	ad_date.SetDate(2201, 10, 28);

	// You need to pass m_Sessino when creating complex types
	Inf::PBDateTime dt(m_Session, year, month, day, hour, minute, second);

	return dt;
}


INF_REGISTER_FUNC(of_strings, L"as_str");
Inf::PBString PBNI_Example::of_strings(Inf::PBString as_str)
{
	// This will convert PowerBuilders utf-16 to 8 bit using Windows API
	std::string ansi_str = as_str.GetString();
	// Creates copy of wstring
	std::wstring unicode_str = as_str.GetWString();

	//Incase you use String as reference you need to do
	as_str.SetString(ansi_str);

	// Again conversion to utf-16
	return Inf::PBString(m_Session, ansi_str + ", received from C++");
}


INF_REGISTER_FUNC(of_blobs, L"abl_blob");
Inf::PBBlob PBNI_Example::of_blobs(Inf::PBBlob abl_blob)
{
	// PBBlob is just a wrapper, GetData returns a pointer to the actual data
	// std vector creates a copy
	std::vector<uint8_t> data_cpp_style(abl_blob.GetData(), abl_blob.GetData() + abl_blob.Size());

	for (uint8_t& byte : data_cpp_style)
	{
		byte |= 0b01010101;
	}

	uint8_t data[] = { 10, 230, 77 };
	// This creates a copy
	abl_blob.SetData(data, sizeof(data));
	// If youre passing blobs by reference you dont need to do SetData if you write to GetData directly

	// Also creates a copy of the vectors data
	return Inf::PBBlob(m_Session, data_cpp_style.data(), data_cpp_style.size());
}


INF_REGISTER_FUNC(of_objects, L"u_obj");
Inf::PBObject<L"u_pbni_ex"> PBNI_Example::of_objects(Inf::PBObject<L"u_pbni_ex"> u_obj)
{
	return u_obj;

	if (!u_obj.IsNull())
	{
		// Passing (m_Session, 0) wil create a null object with complex types
		Inf::PBObject<L"u_pbni_ex"> null_obj(m_Session, 0);

		// You can invoke methods, you only need to give the Return Type
		u_obj.Invoke<Inf::PBObject<L"u_pbni_ex">>(L"of_objects", PBRT_FUNCTION, null_obj);
	}

	// Setting and getting fields
	// This will error because u_pbni_ex doesnt have fields
	Inf::PBInt x = u_obj.GetField<Inf::PBInt>(L"some_field");
	x += 10;
	u_obj.SetField(L"other_field", x);


	u_obj.GetArrayField<Inf::PBInt>(L"arraysss");
	u_obj.GetObjectField<L"u_other_type">(L"subclass?");
	u_obj.GetObjectField<L"u_other_type.st_sub_type", pbgroup_structure>(L"struct");

	return Inf::PBObject<L"u_pbni_ex">(m_Session);
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
