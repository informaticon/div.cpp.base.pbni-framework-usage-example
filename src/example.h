#pragma once

#include <Framework.h>
#include <PBTypes.h>

class PBNI_Example : public Inf::PBNI_Class
{
public:
	PBNI_Example(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name)
		: Inf::PBNI_Class(session, pbobj, pb_class_name)
	{ }

	void basic_func();
	Inf::PBDecimal dec(Inf::PBDecimal& dec);
	Inf::PBBoolean args_ref_return(Inf::PBUint aui_count, Inf::PBLongLong& all_by_ref);

	Inf::PBDateTime dates(Inf::PBDate& ad_date, Inf::PBTime at_time);
	Inf::PBString strings(Inf::PBString as_str);
	Inf::PBBlob blobs(Inf::PBBlob& abl_blob);
	Inf::PBObject<L"u_pbni_example"> objects(Inf::PBObject<L"u_pbni_example"> aa_arr);
	void arrays(Inf::PBArray<Inf::PBInt> aa_arr);

	void throws(Inf::PBString as_err_msg);
};