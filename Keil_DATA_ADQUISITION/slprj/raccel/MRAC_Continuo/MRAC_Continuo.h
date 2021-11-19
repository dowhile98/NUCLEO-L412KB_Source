#ifndef RTW_HEADER_MRAC_Continuo_h_
#define RTW_HEADER_MRAC_Continuo_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef MRAC_Continuo_COMMON_INCLUDES_
#define MRAC_Continuo_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "MRAC_Continuo_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME MRAC_Continuo
#define NSAMPLE_TIMES (3) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (17) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (7)   
#elif NCSTATES != 7
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T fzydadrgwt ; real_T oe2ru0jxkc ; real_T crli2xgbrr ;
real_T iwkxiuph40 ; real_T djlpspxuuq ; real_T gpwt1r0uat ; real_T pm3yqnsioj
; real_T b3n3wdgpy1 ; real_T o4yjjgqgrq ; real_T izhacl3rkl ; real_T
aznrjo51e5 ; real_T miziox3pue ; real_T alpltvbluh ; real_T hofan33icb ;
real_T bk21hemvqf ; real_T icnlxixiqz ; real_T nza0gfyblu ; } B ; typedef
struct { real_T eaos0vs0zq ; int64_T j3ulvxfmd3 ; struct { void * LoggedData
; } hln5rxckl4 ; struct { void * LoggedData ; } mg2nwljwwm ; struct { void *
LoggedData ; } hsysqsjbtj ; int32_T dsbehl4yyz ; int32_T e1b5udgo30 ; } DW ;
typedef struct { real_T bldludabik [ 2 ] ; real_T ecrzjj5wbk [ 2 ] ; real_T
ntupirb2e4 ; real_T p3pqruzt5h ; real_T edjzpwcfcn ; } X ; typedef struct {
real_T bldludabik [ 2 ] ; real_T ecrzjj5wbk [ 2 ] ; real_T ntupirb2e4 ;
real_T p3pqruzt5h ; real_T edjzpwcfcn ; } XDot ; typedef struct { boolean_T
bldludabik [ 2 ] ; boolean_T ecrzjj5wbk [ 2 ] ; boolean_T ntupirb2e4 ;
boolean_T p3pqruzt5h ; boolean_T edjzpwcfcn ; } XDis ; typedef struct {
real_T bldludabik [ 2 ] ; real_T ecrzjj5wbk [ 2 ] ; real_T ntupirb2e4 ;
real_T p3pqruzt5h ; real_T edjzpwcfcn ; } CStateAbsTol ; typedef struct {
real_T bldludabik [ 2 ] ; real_T ecrzjj5wbk [ 2 ] ; real_T ntupirb2e4 ;
real_T p3pqruzt5h ; real_T edjzpwcfcn ; } CXPtMin ; typedef struct { real_T
bldludabik [ 2 ] ; real_T ecrzjj5wbk [ 2 ] ; real_T ntupirb2e4 ; real_T
p3pqruzt5h ; real_T edjzpwcfcn ; } CXPtMax ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T gamma ;
real_T PID_D ; real_T PID_I ; real_T PID_InitialConditionForFilter ; real_T
PID_InitialConditionForIntegrator ; real_T PID_N ; real_T PID_P ; real_T
Transfer_Function_A [ 2 ] ; real_T Transfer_Function_C [ 2 ] ; real_T
TransferFcn_A [ 2 ] ; real_T TransferFcn_C [ 2 ] ; real_T Integrator_IC ;
real_T PulseGenerator_Amp ; real_T PulseGenerator_Period ; real_T
PulseGenerator_Duty ; real_T PulseGenerator_PhaseDelay ; } ; extern const
char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW
rtDW ; extern P rtP ; extern const rtwCAPI_ModelMappingStaticInfo *
MRAC_Continuo_GetCAPIStaticMap ( void ) ; extern SimStruct * const rtS ;
extern const int_T gblNumToFiles ; extern const int_T gblNumFrFiles ; extern
const int_T gblNumFrWksBlocks ; extern rtInportTUtable * gblInportTUtables ;
extern const char * gblInportFileName ; extern const int_T
gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern const
int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern const int_T gblParameterTuningTid ; extern DataMapInfo *
rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ;
void MdlOutputs ( int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T
tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( void ) ;
#endif
