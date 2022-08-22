//@@@+++@@@@******************************************************************
//
// Copyright � Microsoft Corp.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// � Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// � Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//@@@---@@@@******************************************************************


#undef __$adt_add_prop
#undef __$adt_prop
#undef __$adt_remove_prop
#undef __$adt_transfer_prop
#undef __$adt_type_props
#undef __$nonvolatile
#undef __$possibly_notnulltermiated
#undef __$volatile
#undef __allocator
#undef __analysis_assert
#undef __analysis_assume
#undef __analysis_hint
#undef __assume_ValidCompNameA
#undef __assume_ValidCompNameW
#undef __assume_bound
#undef __assume_validated
#undef __bcount
#undef __bcount_opt
#undef __blocksOn
#undef __bound
#undef __byte_readableTo
#undef __byte_writableTo
#undef __callback
#undef __checkReturn
#undef __class_code_content
#undef __control_entrypoint
#undef __data_entrypoint
#undef __deref
#undef __deref_bcount
#undef __deref_bcount_opt
#undef __deref_ecount
#undef __deref_ecount_opt
#undef __deref_in
#undef __deref_in_bcount
#undef __deref_in_bcount_opt
#undef __deref_in_ecount
#undef __deref_in_ecount_opt
#undef __deref_in_opt
#undef __deref_in_range
#undef __deref_in_xcount
#undef __deref_in_xcount_opt
#undef __deref_inout
#undef __deref_inout_bcount
#undef __deref_inout_bcount_full
#undef __deref_inout_bcount_full_opt
#undef __deref_inout_bcount_nz
#undef __deref_inout_bcount_nz_opt
#undef __deref_inout_bcount_opt
#undef __deref_inout_bcount_part
#undef __deref_inout_bcount_part_opt
#undef __deref_inout_bcount_z
#undef __deref_inout_bcount_z_opt
#undef __deref_inout_ecount
#undef __deref_inout_ecount_full
#undef __deref_inout_ecount_full_opt
#undef __deref_inout_ecount_nz
#undef __deref_inout_ecount_nz_opt
#undef __deref_inout_ecount_opt
#undef __deref_inout_ecount_part
#undef __deref_inout_ecount_part_opt
#undef __deref_inout_ecount_z
#undef __deref_inout_ecount_z_opt
#undef __deref_inout_nz
#undef __deref_inout_nz_opt
#undef __deref_inout_opt
#undef __deref_inout_xcount
#undef __deref_inout_xcount_full
#undef __deref_inout_xcount_full_opt
#undef __deref_inout_xcount_opt
#undef __deref_inout_xcount_part
#undef __deref_inout_xcount_part_opt
#undef __deref_inout_z
#undef __deref_inout_z_opt
#undef __deref_nonvolatile
#undef __deref_opt_bcount
#undef __deref_opt_bcount_opt
#undef __deref_opt_ecount
#undef __deref_opt_ecount_opt
#undef __deref_opt_in
#undef __deref_opt_in_bcount
#undef __deref_opt_in_bcount_opt
#undef __deref_opt_in_ecount
#undef __deref_opt_in_ecount_opt
#undef __deref_opt_in_opt
#undef __deref_opt_in_xcount
#undef __deref_opt_in_xcount_opt
#undef __deref_opt_inout
#undef __deref_opt_inout_bcount
#undef __deref_opt_inout_bcount_full
#undef __deref_opt_inout_bcount_full_opt
#undef __deref_opt_inout_bcount_nz
#undef __deref_opt_inout_bcount_nz_opt
#undef __deref_opt_inout_bcount_opt
#undef __deref_opt_inout_bcount_part
#undef __deref_opt_inout_bcount_part_opt
#undef __deref_opt_inout_bcount_z
#undef __deref_opt_inout_bcount_z_opt
#undef __deref_opt_inout_ecount
#undef __deref_opt_inout_ecount_full
#undef __deref_opt_inout_ecount_full_opt
#undef __deref_opt_inout_ecount_nz
#undef __deref_opt_inout_ecount_nz_opt
#undef __deref_opt_inout_ecount_opt
#undef __deref_opt_inout_ecount_part
#undef __deref_opt_inout_ecount_part_opt
#undef __deref_opt_inout_ecount_z
#undef __deref_opt_inout_ecount_z_opt
#undef __deref_opt_inout_nz
#undef __deref_opt_inout_nz_opt
#undef __deref_opt_inout_opt
#undef __deref_opt_inout_xcount
#undef __deref_opt_inout_xcount_full
#undef __deref_opt_inout_xcount_full_opt
#undef __deref_opt_inout_xcount_opt
#undef __deref_opt_inout_xcount_part
#undef __deref_opt_inout_xcount_part_opt
#undef __deref_opt_inout_z
#undef __deref_opt_inout_z_opt
#undef __deref_opt_out
#undef __deref_opt_out_bcount
#undef __deref_opt_out_bcount_full
#undef __deref_opt_out_bcount_full_opt
#undef __deref_opt_out_bcount_nz_opt
#undef __deref_opt_out_bcount_opt
#undef __deref_opt_out_bcount_part
#undef __deref_opt_out_bcount_part_opt
#undef __deref_opt_out_bcount_z_opt
#undef __deref_opt_out_ecount
#undef __deref_opt_out_ecount_full
#undef __deref_opt_out_ecount_full_opt
#undef __deref_opt_out_ecount_nz_opt
#undef __deref_opt_out_ecount_opt
#undef __deref_opt_out_ecount_part
#undef __deref_opt_out_ecount_part_opt
#undef __deref_opt_out_ecount_z_opt
#undef __deref_opt_out_nz_opt
#undef __deref_opt_out_opt
#undef __deref_opt_out_xcount
#undef __deref_opt_out_xcount_full
#undef __deref_opt_out_xcount_full_opt
#undef __deref_opt_out_xcount_opt
#undef __deref_opt_out_xcount_part
#undef __deref_opt_out_xcount_part_opt
#undef __deref_opt_out_z_opt
#undef __deref_opt_xcount
#undef __deref_opt_xcount_opt
#undef __deref_out
#undef __deref_out_bcount
#undef __deref_out_bcount_full
#undef __deref_out_bcount_full_opt
#undef __deref_out_bcount_nz
#undef __deref_out_bcount_nz_opt
#undef __deref_out_bcount_opt
#undef __deref_out_bcount_part
#undef __deref_out_bcount_part_opt
#undef __deref_out_bcount_z
#undef __deref_out_bcount_z_opt
#undef __deref_out_bound
#undef __deref_out_ecount
#undef __deref_out_ecount_full
#undef __deref_out_ecount_full_opt
#undef __deref_out_ecount_nz
#undef __deref_out_ecount_nz_opt
#undef __deref_out_ecount_opt
#undef __deref_out_ecount_part
#undef __deref_out_ecount_part_opt
#undef __deref_out_ecount_z
#undef __deref_out_ecount_z_opt
#undef __deref_out_nz
#undef __deref_out_nz_opt
#undef __deref_out_opt
#undef __deref_out_range
#undef __deref_out_range
#undef __deref_out_xcount
#undef __deref_out_xcount
#undef __deref_out_xcount_full
#undef __deref_out_xcount_full_opt
#undef __deref_out_xcount_opt
#undef __deref_out_xcount_part
#undef __deref_out_xcount_part_opt
#undef __deref_out_z
#undef __deref_out_z_opt
#undef __deref_volatile
#undef __deref_xcount
#undef __deref_xcount_opt
#undef __ecount
#undef __ecount_opt
#undef __elem_readableTo
#undef __elem_writableTo
#undef __encoded_array
#undef __encoded_pointer
#undef __exceptthat
#undef __fallthrough
#undef __field_bcount
#undef __field_bcount_full
#undef __field_bcount_full_opt
#undef __field_bcount_opt
#undef __field_bcount_part
#undef __field_bcount_part_opt
#undef __field_data_source
#undef __field_ecount
#undef __field_ecount_full
#undef __field_ecount_full_opt
#undef __field_ecount_opt
#undef __field_ecount_part
#undef __field_ecount_part_opt
#undef __field_encoded_array
#undef __field_encoded_pointer
#undef __field_range
#undef __field_xcount
#undef __field_xcount_full
#undef __field_xcount_full_opt
#undef __field_xcount_opt
#undef __field_xcount_part
#undef __field_xcount_part_opt
#undef __file_parser
#undef __file_parser_class
#undef __file_parser_library
#undef __format_string
#undef __format_string
#undef __gdi_entry
#undef __in
#undef __in_awcount
#undef __in_bcount
#undef __in_bcount_nz
#undef __in_bcount_nz_opt
#undef __in_bcount_opt
#undef __in_bcount_z
#undef __in_bcount_z_opt
#undef __in_bound
#undef __in_data_source
#undef __in_ecount
#undef __in_ecount_nz
#undef __in_ecount_nz_opt
#undef __in_ecount_opt
#undef __in_ecount_z
#undef __in_ecount_z_opt
#undef __in_nz
#undef __in_nz_opt
#undef __in_opt
#undef __in_range
#undef __in_xcount
#undef __in_xcount_opt
#undef __in_z
#undef __in_z_opt
#undef __inexpressible_readableTo
#undef __inexpressible_writableTo
#undef __inner_assume_bound
#undef __inner_assume_bound_dec
#undef __inner_assume_validated
#undef __inner_assume_validated_dec
#undef __inner_blocksOn
#undef __inner_bound
#undef __inner_callback
#undef __inner_checkReturn
#undef __inner_control_entrypoint
#undef __inner_data_entrypoint
#undef __inner_data_source
#undef __inner_encoded
#undef __inner_fallthrough
#undef __inner_fallthrough_dec
#undef __inner_out_validated
#undef __inner_override
#undef __inner_range
#undef __inner_success
#undef __inner_transfer
#undef __inner_typefix
#undef __inout
#undef __inout_bcount
#undef __inout_bcount_full
#undef __inout_bcount_full_opt
#undef __inout_bcount_nz
#undef __inout_bcount_nz_opt
#undef __inout_bcount_opt
#undef __inout_bcount_part
#undef __inout_bcount_part_opt
#undef __inout_bcount_z
#undef __inout_bcount_z_opt
#undef __inout_ecount
#undef __inout_ecount_full
#undef __inout_ecount_full_opt
#undef __inout_ecount_nz
#undef __inout_ecount_nz_opt
#undef __inout_ecount_opt
#undef __inout_ecount_part
#undef __inout_ecount_part_opt
#undef __inout_ecount_z
#undef __inout_ecount_z_opt
#undef __inout_ecount_z_opt
#undef __inout_nz
#undef __inout_nz_opt
#undef __inout_opt
#undef __inout_xcount
#undef __inout_xcount_full
#undef __inout_xcount_full_opt
#undef __inout_xcount_opt
#undef __inout_xcount_part
#undef __inout_xcount_part_opt
#undef __inout_z
#undef __inout_z_opt
#undef __kernel_entry
#undef __maybenull
#undef __maybereadonly
#undef __maybevalid
#undef __nonvolatile
#undef __notnull
#undef __notreadonly
#undef __notvalid
#undef __null
#undef __nullnullterminated
#undef __nullterminated
#undef __out
#undef __out_awcount
#undef __out_bcount
#undef __out_bcount_full
#undef __out_bcount_full_opt
#undef __out_bcount_nz
#undef __out_bcount_nz_opt
#undef __out_bcount_opt
#undef __out_bcount_part
#undef __out_bcount_part_opt
#undef __out_bcount_z
#undef __out_bcount_z_opt
#undef __out_bound
#undef __out_data_source
#undef __out_ecount
#undef __out_ecount_full
#undef __out_ecount_full_opt
#undef __out_ecount_nz
#undef __out_ecount_nz_opt
#undef __out_ecount_opt
#undef __out_ecount_part
#undef __out_ecount_part_opt
#undef __out_ecount_z
#undef __out_ecount_z_opt
#undef __out_has_adt_prop
#undef __out_has_type_adt_props
#undef __out_not_has_adt_prop
#undef __out_nz
#undef __out_nz_opt
#undef __out_opt
#undef __out_range
#undef __out_transfer_adt_prop
#undef __out_validated
#undef __out_xcount
#undef __out_xcount_full
#undef __out_xcount_full_opt
#undef __out_xcount_opt
#undef __out_xcount_part
#undef __out_xcount_part_opt
#undef __out_z
#undef __override
#undef __possibly_notnulltermiated
#undef __post
#undef __postcond
#undef __pre
#undef __precond
#undef __range
#undef __readableTo
#undef __readonly
#undef __refparam
#undef __reserved
#undef __rpc_entry
#undef __source_code_content
#undef __struct_bcount
#undef __struct_xcount
#undef __success
#undef __this_out_data_source
#undef __this_out_validated
#undef __transfer
#undef __type_has_adt_prop
#undef __typefix
#undef __valid
#undef __volatile
#undef __writableTo
#undef __xcount
#undef __xcount_opt