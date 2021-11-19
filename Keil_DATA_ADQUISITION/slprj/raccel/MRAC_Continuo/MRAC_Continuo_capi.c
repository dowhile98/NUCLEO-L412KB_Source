#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "MRAC_Continuo_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#ifndef SS_INT64
#define SS_INT64  15
#endif
#ifndef SS_UINT64
#define SS_UINT64  16
#endif
#else
#include "builtin_typeid_types.h"
#include "MRAC_Continuo.h"
#include "MRAC_Continuo_capi.h"
#include "MRAC_Continuo_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"MRAC_Continuo/Pulse Generator" ) , TARGET_STRING ( "r" ) , 0 , 0 , 0 , 0 , 0
} , { 1 , 0 , TARGET_STRING ( "MRAC_Continuo/Sum1" ) , TARGET_STRING ( "e" )
, 0 , 0 , 0 , 0 , 1 } , { 2 , 0 , TARGET_STRING (
"MRAC_Continuo/Adaptive Mechanism/gamma" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 3 , 0 , TARGET_STRING (
"MRAC_Continuo/Adaptive Mechanism/Integrator" ) , TARGET_STRING ( "theta" ) ,
0 , 0 , 0 , 0 , 1 } , { 4 , 0 , TARGET_STRING (
"MRAC_Continuo/Adaptive Mechanism/Product" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 5 , 0 , TARGET_STRING ( "MRAC_Continuo/Controller/Mul" ) ,
TARGET_STRING ( "U" ) , 0 , 0 , 0 , 0 , 1 } , { 6 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/Sum" ) , TARGET_STRING ( "Error" ) , 0 , 0 , 0 , 0
, 1 } , { 7 , 0 , TARGET_STRING ( "MRAC_Continuo/DC MOTOR/Transfer Fcn" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"MRAC_Continuo/Reference_Model/Transfer_Function" ) , TARGET_STRING ( "Ym" )
, 0 , 0 , 0 , 0 , 1 } , { 9 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/D Gain/Internal Parameters/Derivative Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 10 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/Filter/Cont. Filter/Filter" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 11 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/Filter/Cont. Filter/SumD" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 12 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/I Gain/Internal Parameters/Integral Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 13 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/Integrator/Continuous/Integrator" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 14 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/N Gain/Internal Parameters/Filter Coefficient"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 15 , 0 , TARGET_STRING (
 "MRAC_Continuo/Controller/PID/Parallel P Gain/Internal Parameters/Proportional Gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 16 , 0 , TARGET_STRING (
"MRAC_Continuo/Controller/PID/Sum/Sum_PID/Sum" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 17 ,
TARGET_STRING ( "MRAC_Continuo/Pulse Generator" ) , TARGET_STRING (
"Amplitude" ) , 0 , 0 , 0 } , { 18 , TARGET_STRING (
"MRAC_Continuo/Pulse Generator" ) , TARGET_STRING ( "Period" ) , 0 , 0 , 0 }
, { 19 , TARGET_STRING ( "MRAC_Continuo/Pulse Generator" ) , TARGET_STRING (
"PulseWidth" ) , 0 , 0 , 0 } , { 20 , TARGET_STRING (
"MRAC_Continuo/Pulse Generator" ) , TARGET_STRING ( "PhaseDelay" ) , 0 , 0 ,
0 } , { 21 , TARGET_STRING ( "MRAC_Continuo/Adaptive Mechanism/Integrator" )
, TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 22 , TARGET_STRING (
"MRAC_Continuo/Controller/PID" ) , TARGET_STRING ( "P" ) , 0 , 0 , 0 } , { 23
, TARGET_STRING ( "MRAC_Continuo/Controller/PID" ) , TARGET_STRING ( "I" ) ,
0 , 0 , 0 } , { 24 , TARGET_STRING ( "MRAC_Continuo/Controller/PID" ) ,
TARGET_STRING ( "D" ) , 0 , 0 , 0 } , { 25 , TARGET_STRING (
"MRAC_Continuo/Controller/PID" ) , TARGET_STRING ( "N" ) , 0 , 0 , 0 } , { 26
, TARGET_STRING ( "MRAC_Continuo/Controller/PID" ) , TARGET_STRING (
"InitialConditionForIntegrator" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING (
"MRAC_Continuo/Controller/PID" ) , TARGET_STRING (
"InitialConditionForFilter" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING (
"MRAC_Continuo/DC MOTOR/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 1 , 0 }
, { 29 , TARGET_STRING ( "MRAC_Continuo/DC MOTOR/Transfer Fcn" ) ,
TARGET_STRING ( "C" ) , 0 , 2 , 0 } , { 30 , TARGET_STRING (
"MRAC_Continuo/Reference_Model/Transfer_Function" ) , TARGET_STRING ( "A" ) ,
0 , 1 , 0 } , { 31 , TARGET_STRING (
"MRAC_Continuo/Reference_Model/Transfer_Function" ) , TARGET_STRING ( "C" ) ,
0 , 2 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 32 , TARGET_STRING (
"gamma" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . iwkxiuph40 , & rtB . hofan33icb ,
& rtB . icnlxixiqz , & rtB . crli2xgbrr , & rtB . bk21hemvqf , & rtB .
alpltvbluh , & rtB . djlpspxuuq , & rtB . oe2ru0jxkc , & rtB . fzydadrgwt , &
rtB . b3n3wdgpy1 , & rtB . o4yjjgqgrq , & rtB . izhacl3rkl , & rtB .
nza0gfyblu , & rtB . pm3yqnsioj , & rtB . aznrjo51e5 , & rtB . gpwt1r0uat , &
rtB . miziox3pue , & rtP . PulseGenerator_Amp , & rtP . PulseGenerator_Period
, & rtP . PulseGenerator_Duty , & rtP . PulseGenerator_PhaseDelay , & rtP .
Integrator_IC , & rtP . PID_P , & rtP . PID_I , & rtP . PID_D , & rtP . PID_N
, & rtP . PID_InitialConditionForIntegrator , & rtP .
PID_InitialConditionForFilter , & rtP . TransferFcn_A [ 0 ] , & rtP .
TransferFcn_C [ 0 ] , & rtP . Transfer_Function_A [ 0 ] , & rtP .
Transfer_Function_C [ 0 ] , & rtP . gamma , } ; static int32_T *
rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 , 2 , 1 , 1 , 2 } ; static const real_T rtcapiStoredFloats [ ] = { -
2.0 , 0.0 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , (
NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 2 ,
0 } , { ( const void * ) & rtcapiStoredFloats [ 1 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , 0 , 0 } } ; static rtwCAPI_ModelMappingStaticInfo
mmiStatic = { { rtBlockSignals , 17 , ( NULL ) , 0 , ( NULL ) , 0 } , {
rtBlockParameters , 15 , rtModelParameters , 1 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 3999652399U , 1585833331U , 3712475836U ,
4070331143U } , ( NULL ) , 0 , 0 } ; const rtwCAPI_ModelMappingStaticInfo *
MRAC_Continuo_GetCAPIStaticMap ( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void MRAC_Continuo_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void MRAC_Continuo_host_InitializeDataMapInfo (
MRAC_Continuo_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
