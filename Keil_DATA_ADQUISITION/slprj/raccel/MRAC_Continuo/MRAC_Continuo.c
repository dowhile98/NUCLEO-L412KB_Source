#include "rt_logging_mmi.h"
#include "MRAC_Continuo_capi.h"
#include <math.h>
#include "MRAC_Continuo.h"
#include "MRAC_Continuo_private.h"
#include "MRAC_Continuo_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 3 ; const char_T
* gbl_raccel_Version = "9.3 (R2020a) 18-Nov-2019" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
"slprj\\raccel\\MRAC_Continuo\\MRAC_Continuo_Jpattern.mat" ; const int_T
gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern void * gblAperiodicPartitionHitTimes ; const int_T
gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [ ] = { - 1 }
; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1 } ; const char *
raccelLoadInputsAndAperiodicHitTimes ( const char * inportFileName , int *
matFileFormat ) { return rt_RapidReadInportsMatFile ( inportFileName ,
matFileFormat , 1 ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ; void MdlInitialize ( void ) { rtX . bldludabik [ 0 ] = 0.0 ; rtX
. ecrzjj5wbk [ 0 ] = 0.0 ; rtX . bldludabik [ 1 ] = 0.0 ; rtX . ecrzjj5wbk [
1 ] = 0.0 ; rtX . ntupirb2e4 = rtP . Integrator_IC ; rtX . p3pqruzt5h = rtP .
PID_InitialConditionForIntegrator ; rtX . edjzpwcfcn = rtP .
PID_InitialConditionForFilter ; } void MdlEnable ( void ) { rtDW . dsbehl4yyz
= 1 ; _ssSetSampleHit ( rtS , 2 , 1 ) ; _ssSetTaskTime ( rtS , 2 , ssGetT (
rtS ) ) ; _ssSetVarNextHitTime ( rtS , 0 , ssGetT ( rtS ) ) ; ; } void
MdlStart ( void ) { { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ;
void * r2 = ( NULL ) ; void * * pOSigstreamManagerAddr = ( NULL ) ; const int
maxErrorBufferSize = 16384 ; char errMsgCreatingOSigstreamManager [ 16384 ] ;
bool errorCreatingOSigstreamManager = false ; const char *
errorAddingR2SharedResource = ( NULL ) ; * slioCatalogueAddr =
rtwGetNewSlioCatalogue ( rt_GetMatSigLogSelectorFileName ( ) ) ;
errorAddingR2SharedResource = rtwAddR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) , 1 ) ; if (
errorAddingR2SharedResource != ( NULL ) ) { rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = ( NULL ) ; ssSetErrorStatus ( rtS
, errorAddingR2SharedResource ) ; return ; } r2 = rtwGetR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
pOSigstreamManagerAddr = rt_GetOSigstreamManagerAddr ( ) ;
errorCreatingOSigstreamManager = rtwOSigstreamManagerCreateInstance (
rt_GetMatSigLogSelectorFileName ( ) , r2 , pOSigstreamManagerAddr ,
errMsgCreatingOSigstreamManager , maxErrorBufferSize ) ; if (
errorCreatingOSigstreamManager ) { * pOSigstreamManagerAddr = ( NULL ) ;
ssSetErrorStatus ( rtS , errMsgCreatingOSigstreamManager ) ; return ; } } {
bool externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( ) ; rtwISigstreamManagerGetInputIsInDatasetFormat (
pISigstreamManager , & externalInputIsInDatasetFormat ) ; if (
externalInputIsInDatasetFormat ) { } } MdlInitialize ( ) ; MdlEnable ( ) ; }
void MdlOutputs ( int_T tid ) { real_T taskTimeV ; real_T ratio ; uint32_T
numCycles ; rtB . fzydadrgwt = 0.0 ; rtB . fzydadrgwt += rtP .
Transfer_Function_C [ 0 ] * rtX . bldludabik [ 0 ] ; rtB . fzydadrgwt += rtP
. Transfer_Function_C [ 1 ] * rtX . bldludabik [ 1 ] ; rtB . oe2ru0jxkc = 0.0
; rtB . oe2ru0jxkc += rtP . TransferFcn_C [ 0 ] * rtX . ecrzjj5wbk [ 0 ] ;
rtB . oe2ru0jxkc += rtP . TransferFcn_C [ 1 ] * rtX . ecrzjj5wbk [ 1 ] ; rtB
. crli2xgbrr = rtX . ntupirb2e4 ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) {
taskTimeV = ssGetTaskTime ( rtS , 2 ) ; if ( ssGetTNextWasAdjusted ( rtS , 2
) ) { rtDW . eaos0vs0zq = _ssGetVarNextHitTime ( rtS , 0 ) ; } if ( rtDW .
dsbehl4yyz != 0 ) { rtDW . dsbehl4yyz = 0 ; if ( taskTimeV >= rtP .
PulseGenerator_PhaseDelay ) { ratio = ( taskTimeV - rtP .
PulseGenerator_PhaseDelay ) / rtP . PulseGenerator_Period ; numCycles = (
uint32_T ) muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T
) ( numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; }
rtDW . j3ulvxfmd3 = numCycles ; ratio = ( ( real_T ) numCycles * rtP .
PulseGenerator_Period + rtP . PulseGenerator_PhaseDelay ) + rtP .
PulseGenerator_Duty * rtP . PulseGenerator_Period / 100.0 ; if ( taskTimeV <
ratio ) { rtDW . e1b5udgo30 = 1 ; rtDW . eaos0vs0zq = ratio ; } else { rtDW .
e1b5udgo30 = 0 ; rtDW . eaos0vs0zq = ( real_T ) ( numCycles + 1U ) * rtP .
PulseGenerator_Period + rtP . PulseGenerator_PhaseDelay ; } } else { rtDW .
j3ulvxfmd3 = rtP . PulseGenerator_PhaseDelay != 0.0 ? - 1 : 0 ; rtDW .
e1b5udgo30 = 0 ; rtDW . eaos0vs0zq = rtP . PulseGenerator_PhaseDelay ; } }
else { if ( rtDW . eaos0vs0zq <= taskTimeV ) { if ( rtDW . e1b5udgo30 == 1 )
{ rtDW . e1b5udgo30 = 0 ; rtDW . eaos0vs0zq = ( real_T ) ( rtDW . j3ulvxfmd3
+ 1LL ) * rtP . PulseGenerator_Period + rtP . PulseGenerator_PhaseDelay ; }
else { rtDW . j3ulvxfmd3 ++ ; rtDW . e1b5udgo30 = 1 ; rtDW . eaos0vs0zq = (
rtP . PulseGenerator_Duty * rtP . PulseGenerator_Period * 0.01 + ( real_T )
rtDW . j3ulvxfmd3 * rtP . PulseGenerator_Period ) + rtP .
PulseGenerator_PhaseDelay ; } } } _ssSetVarNextHitTime ( rtS , 0 , rtDW .
eaos0vs0zq ) ; if ( rtDW . e1b5udgo30 == 1 ) { rtB . iwkxiuph40 = rtP .
PulseGenerator_Amp ; } else { rtB . iwkxiuph40 = 0.0 ; } } rtB . djlpspxuuq =
rtB . iwkxiuph40 - rtB . oe2ru0jxkc ; rtB . gpwt1r0uat = rtP . PID_P * rtB .
djlpspxuuq ; rtB . pm3yqnsioj = rtX . p3pqruzt5h ; rtB . b3n3wdgpy1 = rtP .
PID_D * rtB . djlpspxuuq ; rtB . o4yjjgqgrq = rtX . edjzpwcfcn ; rtB .
izhacl3rkl = rtB . b3n3wdgpy1 - rtB . o4yjjgqgrq ; rtB . aznrjo51e5 = rtP .
PID_N * rtB . izhacl3rkl ; rtB . miziox3pue = ( rtB . gpwt1r0uat + rtB .
pm3yqnsioj ) + rtB . aznrjo51e5 ; rtB . alpltvbluh = rtB . miziox3pue * rtB .
crli2xgbrr ; rtB . hofan33icb = rtB . oe2ru0jxkc - rtB . fzydadrgwt ; rtB .
bk21hemvqf = rtB . fzydadrgwt * rtB . hofan33icb ; rtB . icnlxixiqz = - rtP .
gamma * rtB . bk21hemvqf ; rtB . nza0gfyblu = rtP . PID_I * rtB . djlpspxuuq
; UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { XDot * _rtXdot ;
_rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; _rtXdot -> bldludabik [ 0 ] = 0.0
; _rtXdot -> bldludabik [ 0 ] += rtP . Transfer_Function_A [ 0 ] * rtX .
bldludabik [ 0 ] ; _rtXdot -> bldludabik [ 1 ] = 0.0 ; _rtXdot -> bldludabik
[ 0 ] += rtP . Transfer_Function_A [ 1 ] * rtX . bldludabik [ 1 ] ; _rtXdot
-> bldludabik [ 1 ] += rtX . bldludabik [ 0 ] ; _rtXdot -> bldludabik [ 0 ]
+= rtB . iwkxiuph40 ; _rtXdot -> ecrzjj5wbk [ 0 ] = 0.0 ; _rtXdot ->
ecrzjj5wbk [ 0 ] += rtP . TransferFcn_A [ 0 ] * rtX . ecrzjj5wbk [ 0 ] ;
_rtXdot -> ecrzjj5wbk [ 1 ] = 0.0 ; _rtXdot -> ecrzjj5wbk [ 0 ] += rtP .
TransferFcn_A [ 1 ] * rtX . ecrzjj5wbk [ 1 ] ; _rtXdot -> ecrzjj5wbk [ 1 ] +=
rtX . ecrzjj5wbk [ 0 ] ; _rtXdot -> ecrzjj5wbk [ 0 ] += rtB . alpltvbluh ;
_rtXdot -> ntupirb2e4 = rtB . icnlxixiqz ; _rtXdot -> p3pqruzt5h = rtB .
nza0gfyblu ; _rtXdot -> edjzpwcfcn = rtB . aznrjo51e5 ; } void MdlProjection
( void ) { } void MdlTerminate ( void ) { if ( rt_slioCatalogue ( ) != ( NULL
) ) { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ;
rtwSaveDatasetsToMatFile ( rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( )
) , rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 7 ) ;
ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
3 ) ; ssSetNumBlocks ( rtS , 20 ) ; ssSetNumBlockIO ( rtS , 17 ) ;
ssSetNumBlockParams ( rtS , 20 ) ; } void MdlInitializeSampleTimes ( void ) {
ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , - 2.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS , 2 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 3999652399U ) ;
ssSetChecksumVal ( rtS , 1 , 1585833331U ) ; ssSetChecksumVal ( rtS , 2 ,
3712475836U ) ; ssSetChecksumVal ( rtS , 3 , 4070331143U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 17 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
MRAC_Continuo_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS
, true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "MRAC_Continuo" ) ;
ssSetPath ( rtS , "MRAC_Continuo" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal
( rtS , 50.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo
. loggingInterval = NULL ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; }
{ { static int_T rt_LoggedStateWidths [ ] = { 2 , 2 , 1 , 1 , 1 } ; static
int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 } ; static int_T
rt_LoggedStateDimensions [ ] = { 2 , 2 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE } ; static int_T rt_LoggedStateComplexSignals [ ] = { 0
, 0 , 0 , 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) } ; static const char_T * rt_LoggedStateLabels [ ] = {
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" } ; static const char_T
* rt_LoggedStateBlockNames [ ] = {
"MRAC_Continuo/Reference_Model/Transfer_Function" ,
"MRAC_Continuo/DC MOTOR/Transfer Fcn" ,
"MRAC_Continuo/Adaptive Mechanism/Integrator" ,
"MRAC_Continuo/Controller/PID/Integrator/Continuous/Integrator" ,
"MRAC_Continuo/Controller/PID/Filter/Cont. Filter/Filter" } ; static const
char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" , "" } ; static
boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 } ; static
RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 5 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 5 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . bldludabik [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . ecrzjj5wbk [ 0 ] ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . ntupirb2e4 ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . p3pqruzt5h ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . edjzpwcfcn ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 7 ] ;
static real_T absTol [ 7 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 } ; static uint8_T absTolControl [ 7 ] = { 0U , 0U , 0U , 0U
, 0U , 0U , 0U } ; static real_T contStateJacPerturbBoundMinVec [ 7 ] ;
static real_T contStateJacPerturbBoundMaxVec [ 7 ] ; static
ssNonContDerivSigInfo nonContDerivSigInfo [ 1 ] = { { 1 * sizeof ( real_T ) ,
( char * ) ( & rtB . iwkxiuph40 ) , ( NULL ) } } ; { int i ; for ( i = 0 ; i
< 7 ; ++ i ) { contStateJacPerturbBoundMinVec [ i ] = 0 ;
contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } } ssSetSolverRelTol (
rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 )
; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 1.0 ) ; ssSetSolverMaxOrder ( rtS , - 1 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 0 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
1 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS ,
"VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
ssSetSolverConsistencyChecking ( rtS , 0 ) ; ssSetSolverAdaptiveZcDetection (
rtS , 0 ) ; ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector (
rtS , absTol ) ; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ;
ssSetModelLogDataIfInInterval ( rtS , rt_UpdateTXXFYLogVars ) ;
ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 3999652399U ) ; ssSetChecksumVal ( rtS , 1 ,
1585833331U ) ; ssSetChecksumVal ( rtS , 2 , 3712475836U ) ; ssSetChecksumVal
( rtS , 3 , 4070331143U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 1 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; } return
rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = - 1 ; void MdlOutputsParameterSampleTime
( int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
