#pragma once

#include <Framework.h>
#include <PBTypes.h>

class PBNI_Example : public Inf::PBNI_Class
{
public:
	inline std::wstring GetPBName() override { return L"u_pbni_example"; }

	void of_basic_func();
	Inf::PBDecimal of_dec(Inf::PBDecimal& dec);
	Inf::PBBoolean of_args_ref_return(Inf::PBUint aui_count, Inf::PBLongLong& all_by_ref);

	Inf::PBDateTime of_dates(Inf::PBDate& ad_date, Inf::PBTime at_time);
	Inf::PBString of_strings(Inf::PBString as_str);
	Inf::PBBlob of_blobs(Inf::PBBlob& abl_blob);
	Inf::PBObject<L"u_pbni_example"> of_objects(Inf::PBObject<L"u_pbni_example"> aa_arr);
	void of_arrays(Inf::PBArray<Inf::PBInt> aa_arr);

	void of_throw(Inf::PBString as_err_msg);
};