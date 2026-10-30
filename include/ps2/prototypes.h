/* Signatures of functions recovered under the image's func_XXXXXXXX names; the comment on each line is a working name.
 *
 * Hand-maintained. UNVERIFIED unless a matched definition of the same function confirms the declaration: parameter and
 * return types are recovered guesses (64-bit values appear as u64). Used by the m2c context and by drafts that call these
 * functions; a definition in a translation unit takes precedence over a line here. Structures are in ps2/recovered_types.h. */
#ifndef PS2_PROTOTYPES_H
#define PS2_PROTOTYPES_H
#include "ps2/recovered_types.h"

extern PS2GameObjectRecord * func_00129160(PS2GameObjectManager *, u64); /* GameObjectManager_FindByName */
extern s32 func_00171A40(void *, void *); /* GameBrain_Configure */
extern void func_00174110(void); /* AIMovement_ResetSearchStatistics */
extern s32 func_00174158(RecoveredRouteStorage *, RecoveredRouteNode *, RecoveredRouteNode *, void *); /* AIMovement_AdvancePathSearch */
extern void func_00175980(PS2CollisionQueue *, u64, s32); /* GameCollisionQueue_QueueByName */
extern s32 func_00175BB0(PS2CollisionQueue *, PS2GameObjectRecord *); /* GameCollisionQueue_FindLive */
extern s32 func_00175BF0(PS2CollisionQueue *, PS2GameObjectRecord *); /* GameCollisionQueue_FindPending */
extern s32 func_00175C30(PS2CollisionQueue*,
                         PS2GameObjectRecord*); /* GameCollisionQueue_FindFree; object argument unused */
extern void func_00175F10(PS2PendingCollision*, PS2GameObjectRecord*, s32); /* GameCollisionQueue_SetPending */
extern void func_00179C60(void *); /* RouteRequest_Clear */
extern void func_00179C88(void *); /* RouteRequest_Pump */
extern void func_00179CD0(void *); /* RouteRequest_PointCount */
extern u64 func_00179CE0(RecoveredRouteRequest *, s32); /* AIRoute_PointAt */
extern f32 * func_00179D40(RecoveredRouteRequest *, s32); /* AIRoute_PointAddress */
extern void func_00179D58(RecoveredRouteRequest *, u64, u64, u8); /* AINavigation_SubmitRouteRequest */
extern void func_00179E50(RecoveredRouteRequest *, void *, u64, u8); /* AINavigation_SubmitRouteFromNode */
extern void func_00179ED0(void *); /* RouteRequest_Resubmit */
extern void func_00179EF0(void *); /* RouteRequest_Release */
extern f32 func_00179F18(RecoveredRouteRequest *); /* AIRoute_EndpointDistance */
extern void func_00179F60(RecoveredRouteRequest *, void *); /* AIRoute_BorrowStorage */
extern void func_00179FD0(RecoveredRouteRequest *); /* RouteRequest_ValidateRoute */
extern u8 func_0017A0A8(RecoveredRouteRequest *); /* AIMovement_AdvanceRouteRequest */
extern u8 func_0017A170(RecoveredRouteRequest *); /* AIMovement_BeginQueuedRoute */
extern u8 func_0017A220(RecoveredRouteRequest *); /* AIMovement_TryDirectRoute */
extern u8 func_0017A320(RecoveredRouteRequest *); /* AIMovement_CollectRouteStart */
extern u8 func_0017A3A0(RecoveredRouteRequest *); /* AIMovement_CollectRouteGoal */
extern u8 func_0017A4A8(RecoveredRouteRequest *); /* AIMovement_RunTimedRouteSearch */
extern u8 func_0017A588(RecoveredRouteRequest *); /* AIMovement_CompressRouteStart */
extern u8 func_0017A720(RecoveredRouteRequest *); /* AIMovement_CompressRouteEnd */
extern u8 func_0017A8D8(RecoveredRouteRequest *); /* AIMovement_CheckFinalRouteLeg */
extern void func_0017A980(RecoveredRouteRequest *); /* RouteRequest_SkipPoint */
extern void func_0017A990(RecoveredRouteRequest *); /* RouteRequest_DropFinalPoint */
extern u8 func_0017A9C8(void *, s64); /* RouteRequest_UpdateDestination */
extern void func_0017A9F8(RecoveredRouteRequest *); /* AIRoute_RemoveFirstPoint */
extern void func_0017AB40(RecoveredRouteRequest *, RecoveredRouteNode *); /* AIRoute_AppendNode */
extern void func_0017AED8(RecoveredRouteRequest *); /* AIRoute_SetEndpoint */
extern void func_0017AF20(RecoveredRouteRequest *, s32, s32); /* AIRoute_RemoveLoops */
extern RecoveredRouteRequest * func_0017B158(void *); /* RouteQueue_Head */
extern u8 func_0017B178(void *, RecoveredRouteRequest *); /* RouteQueue_Contains */
extern void func_0017B3D0(RecoveredNodeSearch *); /* AICover_BeginSearch */
extern u8 func_0017B3F0(RecoveredNodeSearch *); /* AICover_AdvanceSearch */
extern void func_001815D8(RecoveredAIActionStack *, void *); /* AIActionOwner_NotifyIdentityRemoved */
extern void func_00181660(RecoveredAIActionStack *, u32, s32); /* AIActionStack_PushAndEnter */
extern void func_00181810(RecoveredAIActionStack *, RecoveredAIActionHeader *, u32, s32); /* AIActionStack_RequestSuccessor */
extern void func_001818A8(RecoveredAIActionStack *); /* AIActionStack_Pop */
extern void func_00181908(RecoveredAIActionStack *, s32); /* AIActionStack_UnwindAbove */
extern void func_00181960(RecoveredAIActionStack *, RecoveredAIActionHeader *); /* AIActionStack_UnwindAction */
extern s32 func_00181A18(RecoveredAIActionStack *, RecoveredAIActionHeader *); /* AIActionStack_FindAction */
extern void func_00181B88(RecoveredAIActionStack *, RecoveredAIQueuedActionEvent *); /* AIActionStack_DispatchEvent */
extern void func_00181C20(RecoveredAIActionStack *); /* AIActionStack_ExpireTimers */
extern void func_00181D20(RecoveredAIActionStack *); /* AIActionStack_DeliverEvents */
extern void func_00181DF8(RecoveredAIActionStack *); /* AIActionStack_RetireFinished */
extern u8 func_00182410(void *, u64, u8, u8); /* AIActionController_RequestRunOrSprint */
extern u8 func_00182668(void *, u64, u32); /* AIActionController_RequestMovement */
extern u32 func_001829A8(RecoveredAIController *); /* AIAction_IsContinuingState */
extern u8 func_00182BC8(void *); /* AIMovement_CheckLocalRoute */
extern void func_0018B168(void *); /* StallGrace_Pending */
extern void func_00191568(void *); /* MovementMode_BindBase */
extern void func_00191578(void *); /* MovementMode_ResetBase */
extern void func_00191778(void *, s64); /* MovementMode_Retarget */
extern u8 func_00191788(void *); /* MovementMode_Recover */
extern void func_00191790(void *); /* MovementMode_Stop */
extern void func_00191798(void *, s64 *); /* MovementMode_GetTarget */
extern void func_00191B40(void *); /* MovementMode_SetSegment */
extern void func_00191B78(void *); /* MovementMode_IsOffRoute */
extern u8 func_00191C18(void *, s64); /* MovementMode_UpdateTarget */
extern void func_00191C20(void *, void *); /* RouteMovementMode_Bind */
extern u8 func_00191C80(void *); /* RouteMovementMode_Reset */
extern void func_00191D40(void *); /* RouteMovementMode_Update */
extern void func_00191F28(void *); /* AINavigation_ReleaseMovementRoute */
extern void func_001920D8(void *, s64); /* RouteMovementMode_Start */
extern void func_00192140(void *, s64); /* RouteMovementMode_Retarget */
extern void func_001921D8(void *, s64); /* AIMovement_CompleteDestination */
extern void func_001922E8(void *, s64 *); /* RouteMovementMode_GetTarget */
extern void func_00192380(void *, s32); /* AIMovement_SetRoutePolicy */
extern u64 func_00192560(void *, u32 *, f32 *); /* AIMovement_AcceptAvoidance */
extern void func_00192568(void *); /* AIMovement_FinishFollow */
extern void func_00192570(void *); /* RouteMode_ResolveSubmitted */
extern u64 func_00192698(void *); /* AIMovement_FollowCurrentDestination */
extern void func_00192A00(void *); /* RouteMode_StepPhase */
extern void func_00192A78(void *, RecoveredRouteRequest *); /* AIMovement_AcceptCompletedRoute */
extern u32 func_00192D48(void *); /* AIMovement_IsAtFinalRoutePoint */
extern u8 func_00192DC0(void *); /* RouteMovementMode_Recover */
extern void func_00192E50(void *); /* RouteMovementMode_Stop */
extern u8 func_00192FB0(void *, s64); /* RouteMovementMode_UpdateTarget */
extern u32 func_00193040(void *, u64); /* AIMovement_RetargetLive */
extern void func_001930F8(void *, RecoveredRouteRequest *); /* AIMovement_JoinCompletedRoute */
extern void func_001933F0(void *); /* AIMovement_TrimConsumedRoutePoints */
extern u8 func_00193488(void *); /* DirectMovementMode_Reset */
extern void func_001934A8(void *); /* DirectMovementMode_Update */
extern void func_00193568(void *, s64); /* DirectMovementMode_Start */
extern u8 func_001936C0(void *, s64); /* DirectMovementMode_UpdateTarget */
extern u8 func_00193700(void *); /* FormationMovementMode_Reset */
extern void func_00193720(void *); /* FormationMovementMode_Update */
extern void func_00193778(void *, s64); /* FormationMovementMode_Start */
extern void func_00193818(void); /* FormationMovementMode_ContinueToGoal */
extern void func_00193990(RecoveredAIActionHeader *, u8); /* AIAction_Complete */
extern void func_001939E0(RecoveredAIActionHeader *); /* AIAction_UnwindAbove */
extern void func_00193A28(RecoveredAIActionHeader *, u32, s32); /* AIAction_RequestSuccessor */
extern u8 func_00193AF8(RecoveredAIActionHeader *); /* AIAction_IsDeadlineReady */
extern RecoveredAICompletionRecord * func_00193B40(RecoveredAIActionHeader *); /* AIAction_Record */
extern void func_00197D48(RecoveredAIActionHeader *); /* AIAction_LeaveReactionWait */
extern void func_00198458(RecoveredAIActionHeader *); /* AIAction_LeaveMovementPermission */
extern void func_00272488(u64, char *); /* GameName_ToString */
extern void * func_002DFEB0(void *, char *, void *); /* Kaim_CActionAttributeClass_Construct */
extern PS2KaimChildBuffer * func_002E2D40(PS2KaimChildBuffer *); /* Kaim_ChildBuffer_AddChild */
extern PS2KaimChildBuffer * func_002E3100(PS2KaimChildBuffer *, char *, char *); /* Kaim_ChildBuffer_FindChild */
extern PS2KaimChildBuffer * func_002E31E0(PS2KaimChildBuffer *, char *); /* Kaim_ChildBuffer_FindByName */
extern char * func_002E3330(PS2KaimChildBuffer *, char *); /* Kaim_ChildBuffer_FindValue */
extern PS2KaimChildBuffer * func_002E33E0(PS2KaimChildBuffer *, u32); /* Kaim_ChildBuffer_GetChildAt */
extern PS2KaimChildBuffer * func_002E3578(PS2KaimChildBuffer *, char *); /* Kaim_ChildBuffer_SetFirst */
extern PS2KaimChildBuffer * func_002E3630(PS2KaimChildBuffer *, char *); /* Kaim_ChildBuffer_SetName */
extern PS2KaimChildBuffer * func_002E36E8(PS2KaimChildBuffer *, char *); /* Kaim_ChildBuffer_SetValue */
extern char * func_002E3920(PS2KaimChildBuffer *); /* Kaim_ChildBuffer_GetName */
extern void func_002E4CA8(void *); /* Kaim_Entity_ResetBrain */
extern void * func_002E4CE0(void *, s32 *); /* Kaim_Entity_GetAttribute */
extern s32 func_002E74E0(void *, PS2KaimChildBuffer *); /* Kaim_BrainService_Configure */
extern void * func_002E75B8(void *, void *); /* Kaim_BrainService_Construct */
extern PS2KaimBufferSet * func_002E7670(PS2KaimBufferSet *); /* Kaim_BufferSet_Construct */
extern PS2KaimIndexTable * func_002E78D0(PS2KaimIndexTable *); /* Kaim_IndexTable_Construct */
extern PS2KaimParameterTables * func_002E7AC0(PS2KaimParameterTables *); /* Kaim_ParameterTables_Construct */
extern s32 func_002E8650(char *); /* Kaim_ParameterTables_AddPeriodicName */
extern s32 func_002E8740(char *); /* Kaim_ParameterTables_AddAperiodicName */
extern s32 func_002E8830(char *); /* Kaim_ParameterTables_AddEstimatedName */
extern void func_002E8920(PS2KaimParameterTables *, f32); /* Kaim_ParameterTables_Update */
extern s32 func_002E8AB8(PS2KaimParameterTables *, s32, void *); /* Kaim_ParameterTables_Consume */
extern PS2KaimParameterTables * func_002E91C0(void); /* Kaim_ParameterTables_Get */
extern s32 * func_0030E6B8(void *, u32); /* Kaim_CSoundManager_GetCounter */
extern f32 func_00348A38(s32, void *); /* AnimationEvents_Invoke */
extern f32 func_00351B78(PS2AnimationExpression *, void *); /* AnimationExpression_All */
extern f32 func_00351C18(PS2AnimationExpression *, void *); /* AnimationExpression_Any */
extern f32 func_00351CC0(PS2AnimationExpression *, void *); /* AnimationExpression_Parity */
extern f32 func_00351D70(PS2AnimationExpression *, void *); /* AnimationExpression_Not */
extern f32 func_00351DB0(PS2AnimationExpression *, void *); /* AnimationExpression_Equal */
extern f32 func_00351E18(PS2AnimationExpression *, void *); /* AnimationExpression_NotEqual */
extern f32 func_00351E80(PS2AnimationExpression *, void *); /* AnimationExpression_Greater */
extern f32 func_00351EE8(PS2AnimationExpression *, void *); /* AnimationExpression_Less */
extern f32 func_00351F50(PS2AnimationExpression *, void *); /* AnimationExpression_GreaterEqual */
extern f32 func_00351FB8(PS2AnimationExpression *, void *); /* AnimationExpression_LessEqual */
extern f32 func_00352020(PS2AnimationExpression *, void *); /* AnimationExpression_Event */
extern f32 func_00352040(PS2AnimationExpression *, void *); /* AnimationExpression_Constant */
extern f32 func_00352048(PS2AnimationExpression *, void *); /* AnimationExpression_Evaluate */
extern void func_00367460(void); /* SetGsCrt */
extern void func_00367480(s32); /* _Exit */
extern void func_00367540(void); /* AddIntcHandler */
extern void func_00367550(void); /* AddIntcHandler */
extern void func_00367560(void); /* RemoveIntcHandler */
extern void func_00367570(void); /* AddDmacHandler */
extern void func_00367580(void); /* AddDmacHandler */
extern void func_00367590(void); /* RemoveDmacHandler */
extern void func_003675A0(void); /* _EnableIntc */
extern void func_003675B0(void); /* _DisableIntc */
extern void func_003675C0(void); /* _EnableDmac */
extern void func_003675D0(void); /* _DisableDmac */
extern void func_003675E0(void); /* Syscall252 */
extern void func_00367660(void); /* CreateThread */
extern void func_00367670(void); /* DeleteThread */
extern void func_00367680(void); /* _StartThread */
extern void func_003676A0(void); /* ExitDeleteThread */
extern void func_003676B0(void); /* TerminateThread */
extern void func_003676F0(void); /* ChangeThreadPriority */
extern void func_00367710(void); /* RotateThreadReadyQueue */
extern void func_00367750(void); /* GetThreadId */
extern void func_00367760(void); /* ReferThreadStatus */
extern void func_00367780(void); /* SleepThread */
extern void func_00367790(void); /* WakeupThread */
extern void func_003677A0(void); /* _iWakeupThread */
extern void func_003677D0(void); /* SuspendThread */
extern void func_00367840(void); /* EndOfHeap */
extern void func_00367860(void); /* CreateSema */
extern void func_00367870(void); /* DeleteSema */
extern void func_00367880(void); /* SignalSema */
extern void func_00367890(void); /* iSignalSema */
extern void func_003678A0(void); /* WaitSema */
extern void func_003678B0(void); /* PollSema */
extern void func_00367900(void); /* SetOsdConfigParam */
extern void func_00367910(void); /* GetOsdConfigParam */
extern void func_00367AE0(void); /* FlushCache */
extern void func_00367B30(void); /* sceSifStopDma */
extern void func_00367B70(void); /* GetOsdConfigParam2 */
extern void func_00367B80(void); /* GsGetIMR */
extern void func_00367BA0(void); /* GsPutIMR */
extern void func_00367BD0(void); /* SetVSyncFlag */
extern void func_00367C00(void); /* sceSifDmaStat */
extern void func_00367C20(void); /* sceSifSetDma */
extern void func_00367C30(void); /* isceSifSetDma */
extern void func_00367C40(void); /* sceSifSetDChain */
extern void func_00367C50(void); /* isceSifSetDChain */
extern void func_00367C60(void); /* sceSifSetReg */
extern void func_00367C70(void); /* sceSifGetReg */
extern void func_00367C90(void); /* Deci2Call */
extern void func_00367CC0(void); /* GetMemorySize */
extern void func_00367CD0(void); /* _InitTLB */
extern void func_0036D778(void); /* RFU116_SetSyscall */
extern void func_0036D7E0(void); /* RFU116_SetSyscall */
extern void func_0036D838(void); /* RFU091 */
extern void func_0036D9C8(void); /* RFU116_SetSyscall */
extern void func_0036DA20(void); /* RFU091 */
extern void func_0036EC38(void); /* RFU091 */
extern void func_0036EC48(void); /* RFU116_SetSyscall */
extern void func_0036ED20(void); /* RFU086_WaitEvnetFlag */
extern void func_00370168(void *, char *, void *); /* __rtti_si */
extern void func_00370188(void *, char *); /* __rtti_user */
extern void func_00389178(void *, s32); /* Kaim_Object_DeletingDestructor */
extern void * func_00389290(void *); /* Kaim_CFleeAgent_GetClassInfo */
extern void * func_003894D0(void *); /* Kaim_CFollowerAgent_GetClassInfo */
extern void * func_00389550(void *); /* Kaim_CGotoAgent_GetClassInfo */
extern void * func_003895C8(void *); /* Kaim_CHideAgent_GetClassInfo */
extern void * func_00389668(void *); /* Kaim_CPathWayAgent_GetClassInfo */
extern void * func_00389770(void *); /* Kaim_CShooterAgent_GetClassInfo */
extern void * func_00389818(void *); /* Kaim_CWanderAgent_GetClassInfo */
extern void * func_003898E0(void *); /* Kaim_CActionAcceleration_GetClassInfo */
extern void * func_00389A90(void *); /* Kaim_CActionCrouch_GetClassInfo */
extern void * func_00389B58(void *); /* Kaim_CActionJump_GetClassInfo */
extern void * func_00389C20(void *); /* Kaim_CActionRotate_GetClassInfo */
extern void * func_00389CE8(void *); /* Kaim_CActionShoot_GetClassInfo */
extern void * func_00389DE0(void *); /* Kaim_CActionSpeed_GetClassInfo */
extern void * func_00389EA8(void *); /* Kaim_CActionSteering_GetClassInfo */
extern void * func_00389F70(void *); /* Kaim_CEntityCanFly_GetClassInfo */
extern void * func_0038A118(void *); /* Kaim_CEntityEyePosition_GetClassInfo */
extern void * func_0038A210(void *); /* Kaim_CEntityGunPosition_GetClassInfo */
extern void * func_0038A308(void *); /* Kaim_CEntityHeadDirection_GetClassInfo */
extern void * func_0038A400(void *); /* Kaim_CEntityHearingAcuteness_GetClassInfo */
extern void * func_0038A508(void *); /* Kaim_CEntityHeight_GetClassInfo */
extern void * func_0038A5C8(void *); /* Kaim_CEntityKneePosition_GetClassInfo */
extern void * func_0038A6E8(void *); /* Kaim_CEntityLength_GetClassInfo */
extern void * func_0038A7C8(void *); /* Kaim_CEntityMaxSpeed_GetClassInfo */
extern void * func_0038A890(void *); /* Kaim_CEntityTeamSide_GetClassInfo */
extern void * func_0038A950(void *); /* Kaim_CEntityTorsoOrientation_GetClassInfo */
extern void * func_0038AA58(void *); /* Kaim_CEntityVisualAcuteness_GetClassInfo */
extern void * func_0038AB68(void *); /* Kaim_CEntityWidth_GetClassInfo */
extern void * func_0038AC28(void *); /* Kaim_CActionActivate_GetClassInfo */
extern void * func_0038ACF0(void *); /* Kaim_CActionHeadRotate_GetClassInfo */
extern void * func_0038ADD0(void *); /* Kaim_CActionTorsoRotate_GetClassInfo */
extern void * func_0038AEB0(void *); /* Kaim_CActionVerticalSpeed_GetClassInfo */
extern void * func_0038AFA8(void *); /* Kaim_CPathWayManager_GetClassInfo */
extern void * func_0038B140(void *); /* Kaim_CPointMapper_GetClassInfo */
extern void * func_0038B2B8(void *); /* Kaim_CScriptManager_GetClassInfo */
extern PS2KaimClassRegistry * func_0038BA30(void); /* Kaim_AgentClass_GetRegistry */
extern void * func_0038C318(void); /* Kaim_CBrain_TypeInfo */
extern PS2KaimClassRegistry * func_0038C3E0(void); /* Kaim_ServiceClass_GetRegistry */
extern PS2KaimClassDescriptor * func_0038C438(char *); /* Kaim_ServiceClass_FindByName */
extern PS2KaimClassDescriptor * func_0038C4D8(char *); /* Kaim_AgentClass_FindByName */
extern void * func_0038CB28(void); /* Kaim_CEntity_TypeInfo */
extern void * func_0038D390(void); /* Kaim_CBrainService_TypeInfo */
extern s32 func_0038E768(void *, PS2KaimChildBuffer *); /* Kaim_BrainService_IsPrivateChild */
extern void * func_0038EF98(void *); /* Kaim_CTeam_GetClassInfo */
extern void * func_0038FFC0(void *); /* Kaim_CFindNearestData_GetClassInfo */
extern void * func_00390260(void *); /* Kaim_CConstraintShortestPath_GetClassInfo */
extern void * func_003902F8(void *); /* Kaim_CConstraintStealthPath_GetClassInfo */
extern void * func_003903A0(void *); /* Kaim_CConstraintConeVisionStealthPath_GetClassInfo */
extern void * func_00390440(void *); /* Kaim_CConstraintPointToFleePath_GetClassInfo */
extern void * func_00390548(void *); /* Kaim_CSphereConstraint_GetClassInfo */
extern void * func_00390630(void *); /* Kaim_CHeuristicEuclidianDistance_GetClassInfo */
extern void * func_00390748(void *); /* Kaim_CZeroHeuristic_GetClassInfo */
extern void * func_00390808(void *); /* Kaim_CPathCostHeuristic_GetClassInfo */
extern void * func_00390CE8(void *); /* Kaim_CGraphManager_GetClassInfo */
extern void * func_00390E20(void *); /* Kaim_CGraphWrapper_GetClassInfo */
extern void * func_00391120(void *); /* Kaim_CPathCostData_GetClassInfo */
extern void * func_003914B0(void *); /* Kaim_CPathObjectManager_GetClassInfo */
extern void * func_00392DA0(void *); /* Kaim_CAccessWaysData_GetClassInfo */
extern void * func_00393598(void *); /* Kaim_CAstarData_GetClassInfo */
extern void * func_00393928(void *); /* Kaim_CPathFinder_GetClassInfo */
extern void * func_00394220(void *); /* Kaim_CGapDynamicAvoidance_GetClassInfo */
extern void * func_00394C10(void *); /* Kaim_CSoundManager_GetClassInfo */
extern void * func_00394D18(void); /* Kaim_CEntityManager_TypeInfo */
extern void * func_00394D68(void *); /* Kaim_CEntityManager_GetClassInfo */

#endif
