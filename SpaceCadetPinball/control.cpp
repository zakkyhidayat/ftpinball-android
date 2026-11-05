#include "pch.h"
#include "loader.h"
#include "control.h"

#include "pb.h"
#include "winmain.h"
#include "lenient_scores.h"
#include "lenient_lights.h"
#include "lenient_sounds.h"
#include "pinball.h"
#include "TBlocker.h"
#include "TBumper.h"
#include "TComponentGroup.h"
#include "TFlagSpinner.h"
#include "TLight.h"
#include "TLightBargraph.h"
#include "TLightGroup.h"
#include "TLightRollover.h"
#include "TPinballTable.h"
#include "TPopupTarget.h"
#include "TSink.h"
#include "TSoloTarget.h"
#include "TSound.h"
#include "TTripwire.h"
#include "TDrain.h"
#include "TBall.h"
#include "timer.h"
#include "TFlipper.h"
#include "TGate.h"
#include "THole.h"
#include "TKickback.h"
#include "TKickout.h"
#include "TOneway.h"
#include "TRamp.h"
#include "TPlunger.h"
#include "TWall.h"
#include "TTextBox.h"

int control_bump_scores1[] = {500, 1000, 1500, 2000};
int control_roll_scores1[] = {2000};
int control_bump_scores2[] = {1500, 2500, 3500, 4500};
int control_roll_scores2[] = {500};
int control_rebo_score1[] = {500};
int control_oneway4_score1[6] = {15000, 30000, 75000, 30000, 15000, 7500};
int control_ramp_score1[1] = {5000};
int control_roll_score1[1] = {20000};
int control_roll_score2[2] = {5000, 25000};
int control_roll_score3[1] = {10000};
int control_roll_score4[1] = {500};
int control_flag_score1[2] = {500, 2500};
int control_kickout_score1[5] = {10000, 0, 20000, 50000, 150000};
int control_sink_score1[3] = {2500, 5000, 7500};
int control_target_score1[2] = {500, 5000};
int control_target_score2[3] = {1500, 10000, 50000};
int control_target_score3[2] = {500, 1500};
int control_target_score4[1] = {750};
int control_target_score5[1] = {1000};
int control_target_score6[1] = {750};
int control_target_score7[1] = {750};
int control_roll_score5[1] = {10000};
int control_kickout_score2[1] = {20000};
int control_kickout_score3[1] = {50000};


component_tag<TComponentGroup> control_attack_bump_tag = {"attack_bumpers", nullptr};
component_tag<TComponentGroup> control_launch_bump_tag = {"launch_bumpers", nullptr};
component_tag<TBlocker> control_block1_tag = {"v_bloc1", nullptr};
component_tag<TBumper> control_bump1_tag = {"a_bump1", nullptr};
component_tag<TBumper> control_bump2_tag = {"a_bump2", nullptr};
component_tag<TBumper> control_bump3_tag = {"a_bump3", nullptr};
component_tag<TBumper> control_bump4_tag = {"a_bump4", nullptr};
component_tag<TBumper> control_bump5_tag = {"a_bump5", nullptr};
component_tag<TBumper> control_bump6_tag = {"a_bump6", nullptr};
component_tag<TBumper> control_bump7_tag = {"a_bump7", nullptr};
component_tag<TDrain> control_drain_tag = {"drain", nullptr};
component_tag<TFlagSpinner> control_flag1_tag = {"a_flag1", nullptr};
component_tag<TFlagSpinner> control_flag2_tag = {"a_flag2", nullptr};
component_tag<TFlipper> control_flip1_tag = {"a_flip1", nullptr};
component_tag<TFlipper> control_flip2_tag = {"a_flip2", nullptr};
component_tag<TLightBargraph> control_fuel_bargraph_tag = {"fuel_bargraph", nullptr};
component_tag<TGate> control_gate1_tag = {"v_gate1", nullptr};
component_tag<TGate> control_gate2_tag = {"v_gate2", nullptr};
component_tag<TTextBox> control_info_text_box_tag = {"info_text_box", nullptr};
component_tag<TKickback> control_kicker1_tag = {"a_kick1", nullptr};
component_tag<TKickback> control_kicker2_tag = {"a_kick2", nullptr};
component_tag<TKickout> control_kickout1_tag = {"a_kout1", nullptr};
component_tag<TKickout> control_kickout2_tag = {"a_kout2", nullptr};
component_tag<TKickout> control_kickout3_tag = {"a_kout3", nullptr};
component_tag<TLight> control_lite1_tag = {"lite1", nullptr};
component_tag<TLight> control_lite2_tag = {"lite2", nullptr};
component_tag<TLight> control_lite3_tag = {"lite3", nullptr};
component_tag<TLight> control_lite4_tag = {"lite4", nullptr};
component_tag<TLight> control_lite5_tag = {"lite5", nullptr};
component_tag<TLight> control_lite6_tag = {"lite6", nullptr};
component_tag<TLight> control_lite7_tag = {"lite7", nullptr};
component_tag<TLight> control_lite8_tag = {"lite8", nullptr};
component_tag<TLight> control_lite9_tag = {"lite9", nullptr};
component_tag<TLight> control_lite10_tag = {"lite10", nullptr};
component_tag<TLight> control_lite11_tag = {"lite11", nullptr};
component_tag<TLight> control_lite12_tag = {"lite12", nullptr};
component_tag<TLight> control_lite13_tag = {"lite13", nullptr};
component_tag<TLight> control_lite16_tag = {"lite16", nullptr};
component_tag<TLight> control_lite17_tag = {"lite17", nullptr};
component_tag<TLight> control_lite18_tag = {"lite18", nullptr};
component_tag<TLight> control_lite19_tag = {"lite19", nullptr};
component_tag<TLight> control_lite20_tag = {"lite20", nullptr};
component_tag<TLight> control_lite21_tag = {"lite21", nullptr};
component_tag<TLight> control_lite22_tag = {"lite22", nullptr};
component_tag<TLight> control_lite23_tag = {"lite23", nullptr};
component_tag<TLight> control_lite24_tag = {"lite24", nullptr};
component_tag<TLight> control_lite25_tag = {"lite25", nullptr};
component_tag<TLight> control_lite26_tag = {"lite26", nullptr};
component_tag<TLight> control_lite27_tag = {"lite27", nullptr};
component_tag<TLight> control_lite28_tag = {"lite28", nullptr};
component_tag<TLight> control_lite29_tag = {"lite29", nullptr};
component_tag<TLight> control_lite30_tag = {"lite30", nullptr};
component_tag<TLight> control_lite54_tag = {"lite54", nullptr};
component_tag<TLight> control_lite55_tag = {"lite55", nullptr};
component_tag<TLight> control_lite56_tag = {"lite56", nullptr};
component_tag<TLight> control_lite58_tag = {"lite58", nullptr};
component_tag<TLight> control_lite59_tag = {"lite59", nullptr};
component_tag<TLight> control_lite60_tag = {"lite60", nullptr};
component_tag<TLight> control_lite61_tag = {"lite61", nullptr};
component_tag<TLight> control_lite62_tag = {"lite62", nullptr};
component_tag<TLight> control_lite67_tag = {"lite67", nullptr};
component_tag<TLight> control_lite68_tag = {"lite68", nullptr};
component_tag<TLight> control_lite69_tag = {"lite69", nullptr};
component_tag<TLight> control_lite70_tag = {"lite70", nullptr};
component_tag<TLight> control_lite71_tag = {"lite71", nullptr};
component_tag<TLight> control_lite72_tag = {"lite72", nullptr};
component_tag<TLight> control_lite77_tag = {"lite77", nullptr};
component_tag<TLight> control_lite84_tag = {"lite84", nullptr};
component_tag<TLight> control_lite85_tag = {"lite85", nullptr};
component_tag<TLight> control_lite101_tag = {"lite101", nullptr};
component_tag<TLight> control_lite102_tag = {"lite102", nullptr};
component_tag<TLight> control_lite103_tag = {"lite103", nullptr};
component_tag<TLight> control_lite104_tag = {"lite104", nullptr};
component_tag<TLight> control_lite105_tag = {"lite105", nullptr};
component_tag<TLight> control_lite106_tag = {"lite106", nullptr};
component_tag<TLight> control_lite107_tag = {"lite107", nullptr};
component_tag<TLight> control_lite108_tag = {"lite108", nullptr};
component_tag<TLight> control_lite109_tag = {"lite109", nullptr};
component_tag<TLight> control_lite110_tag = {"lite110", nullptr};
component_tag<TLight> control_lite130_tag = {"lite130", nullptr};
component_tag<TLight> control_lite131_tag = {"lite131", nullptr};
component_tag<TLight> control_lite132_tag = {"lite132", nullptr};
component_tag<TLight> control_lite133_tag = {"lite133", nullptr};
component_tag<TLight> control_lite169_tag = {"lite169", nullptr};
component_tag<TLight> control_lite170_tag = {"lite170", nullptr};
component_tag<TLight> control_lite171_tag = {"lite171", nullptr};
component_tag<TLight> control_lite195_tag = {"lite195", nullptr};
component_tag<TLight> control_lite196_tag = {"lite196", nullptr};
component_tag<TLight> control_lite198_tag = {"lite198", nullptr};
component_tag<TLight> control_lite199_tag = {"lite199", nullptr};
component_tag<TLight> control_lite200_tag = {"lite200", nullptr};
component_tag<TLight> control_lite300_tag = {"lite300", nullptr};
component_tag<TLight> control_lite301_tag = {"lite301", nullptr};
component_tag<TLight> control_lite302_tag = {"lite302", nullptr};
component_tag<TLight> control_lite303_tag = {"lite303", nullptr};
component_tag<TLight> control_lite304_tag = {"lite304", nullptr};
component_tag<TLight> control_lite305_tag = {"lite305", nullptr};
component_tag<TLight> control_lite306_tag = {"lite306", nullptr};
component_tag<TLight> control_lite307_tag = {"lite307", nullptr};
component_tag<TLight> control_lite308_tag = {"lite308", nullptr};
component_tag<TLight> control_lite309_tag = {"lite309", nullptr};
component_tag<TLight> control_lite310_tag = {"lite310", nullptr};
component_tag<TLight> control_lite311_tag = {"lite311", nullptr};
component_tag<TLight> control_lite312_tag = {"lite312", nullptr};
component_tag<TLight> control_lite313_tag = {"lite313", nullptr};
component_tag<TLight> control_lite314_tag = {"lite314", nullptr};
component_tag<TLight> control_lite315_tag = {"lite315", nullptr};
component_tag<TLight> control_lite316_tag = {"lite316", nullptr};
component_tag<TLight> control_lite317_tag = {"lite317", nullptr};
component_tag<TLight> control_lite318_tag = {"lite318", nullptr};
component_tag<TLight> control_lite319_tag = {"lite319", nullptr};
component_tag<TLight> control_lite320_tag = {"lite320", nullptr};
component_tag<TLight> control_lite321_tag = {"lite321", nullptr};
component_tag<TLight> control_lite322_tag = {"lite322", nullptr};
component_tag<TLight> control_literoll179_tag = {"literoll179", nullptr};
component_tag<TLight> control_literoll180_tag = {"literoll180", nullptr};
component_tag<TLight> control_literoll181_tag = {"literoll181", nullptr};
component_tag<TLight> control_literoll182_tag = {"literoll182", nullptr};
component_tag<TLight> control_literoll183_tag = {"literoll183", nullptr};
component_tag<TLight> control_literoll184_tag = {"literoll184", nullptr};
component_tag<TLightGroup> control_middle_circle_tag = {"middle_circle", nullptr};
component_tag<TLightGroup> control_lchute_tgt_lights_tag = {"lchute_tgt_lights", nullptr};
component_tag<TLightGroup> control_l_trek_lights_tag = {"l_trek_lights", nullptr};
component_tag<TLightGroup> control_goal_lights_tag = {"goal_lights", nullptr};
component_tag<TLightGroup> control_hyper_lights_tag = {"hyperspace_lights", nullptr};
component_tag<TLightGroup> control_bmpr_inc_lights_tag = {"bmpr_inc_lights", nullptr};
component_tag<TLightGroup> control_bpr_solotgt_lights_tag = {"bpr_solotgt_lights", nullptr};
component_tag<TLightGroup> control_bsink_arrow_lights_tag = {"bsink_arrow_lights", nullptr};
component_tag<TLightGroup> control_bumber_target_lights_tag = {"bumper_target_lights", nullptr};
component_tag<TLightGroup> control_outer_circle_tag = {"outer_circle", nullptr};
component_tag<TLightGroup> control_r_trek_lights_tag = {"r_trek_lights", nullptr};
component_tag<TLightGroup> control_ramp_bmpr_inc_lights_tag = {"ramp_bmpr_inc_lights", nullptr};
component_tag<TLightGroup> control_ramp_tgt_lights_tag = {"ramp_tgt_lights", nullptr};
component_tag<TLightGroup> control_skill_shot_lights_tag = {"skill_shot_lights", nullptr};
component_tag<TLightGroup> control_top_circle_tgt_lights_tag = {"top_circle_tgt_lights", nullptr};
component_tag<TLightGroup> control_top_target_lights_tag = {"top_target_lights", nullptr};
component_tag<TLightGroup> control_worm_hole_lights_tag = {"worm_hole_lights", nullptr};
component_tag<TTextBox> control_mission_text_box_tag = {"mission_text_box", nullptr};
component_tag<TOneway> control_oneway1_tag = {"s_onewy1", nullptr};
component_tag<TOneway> control_oneway4_tag = {"s_onewy4", nullptr};
component_tag<TOneway> control_oneway10_tag = {"s_onewy10", nullptr};
component_tag<TPlunger> control_plunger_tag = {"plunger", nullptr};
component_tag<THole> control_ramp_hole_tag = {"ramp_hole", nullptr};
component_tag<TRamp> control_ramp_tag = {"ramp", nullptr};
component_tag<TWall> control_rebo1_tag = {"v_rebo1", nullptr};
component_tag<TWall> control_rebo2_tag = {"v_rebo2", nullptr};
component_tag<TWall> control_rebo3_tag = {"v_rebo3", nullptr};
component_tag<TWall> control_rebo4_tag = {"v_rebo4", nullptr};
component_tag<TRollover> control_roll1_tag = {"a_roll1", nullptr};
component_tag<TRollover> control_roll2_tag = {"a_roll2", nullptr};
component_tag<TRollover> control_roll3_tag = {"a_roll3", nullptr};
component_tag<TRollover> control_roll4_tag = {"a_roll4", nullptr};
component_tag<TRollover> control_roll5_tag = {"a_roll5", nullptr};
component_tag<TRollover> control_roll6_tag = {"a_roll6", nullptr};
component_tag<TRollover> control_roll7_tag = {"a_roll7", nullptr};
component_tag<TRollover> control_roll8_tag = {"a_roll8", nullptr};
component_tag<TLightRollover> control_roll9_tag = {"a_roll9", nullptr};
component_tag<TRollover> control_roll110_tag = {"a_roll110", nullptr};
component_tag<TRollover> control_roll111_tag = {"a_roll111", nullptr};
component_tag<TRollover> control_roll112_tag = {"a_roll112", nullptr};
component_tag<TRollover> control_roll179_tag = {"a_roll179", nullptr};
component_tag<TRollover> control_roll180_tag = {"a_roll180", nullptr};
component_tag<TRollover> control_roll181_tag = {"a_roll181", nullptr};
component_tag<TRollover> control_roll182_tag = {"a_roll182", nullptr};
component_tag<TRollover> control_roll183_tag = {"a_roll183", nullptr};
component_tag<TRollover> control_roll184_tag = {"a_roll184", nullptr};
component_tag<TSink> control_sink1_tag = {"v_sink1", nullptr};
component_tag<TSink> control_sink2_tag = {"v_sink2", nullptr};
component_tag<TSink> control_sink3_tag = {"v_sink3", nullptr};
component_tag<TSink> control_sink7_tag = {"v_sink7", nullptr};
component_tag<TSound> control_soundwave3_tag = {"soundwave3", nullptr};
component_tag<TSound> control_soundwave7_tag = {"soundwave7", nullptr};
component_tag<TSound> control_soundwave8_tag = {"soundwave8", nullptr};
component_tag<TSound> control_soundwave9_tag = {"soundwave9", nullptr};
component_tag<TSound> control_soundwave10_tag = {"soundwave10", nullptr};
component_tag<TSound> control_soundwave14_1_tag = {"soundwave14", nullptr};
component_tag<TSound> control_soundwave14_2_tag = {"soundwave14", nullptr};
component_tag<TSound> control_soundwave21_tag = {"soundwave21", nullptr};
component_tag<TSound> control_soundwave23_tag = {"soundwave23", nullptr};
component_tag<TSound> control_soundwave24_tag = {"soundwave24", nullptr};
component_tag<TSound> control_soundwave25_tag = {"soundwave25", nullptr};
component_tag<TSound> control_soundwave26_tag = {"soundwave26", nullptr};
component_tag<TSound> control_soundwave27_tag = {"soundwave27", nullptr};
component_tag<TSound> control_soundwave28_tag = {"soundwave28", nullptr};
component_tag<TSound> control_soundwave30_tag = {"soundwave30", nullptr};
component_tag<TSound> control_soundwave35_1_tag = {"soundwave35", nullptr};
component_tag<TSound> control_soundwave35_2_tag = {"soundwave35", nullptr};
component_tag<TSound> control_soundwave36_1_tag = {"soundwave36", nullptr};
component_tag<TSound> control_soundwave36_2_tag = {"soundwave36", nullptr};
component_tag<TSound> control_soundwave38_tag = {"soundwave38", nullptr};
component_tag<TSound> control_soundwave39_tag = {"soundwave39", nullptr};
component_tag<TSound> control_soundwave40_tag = {"soundwave40", nullptr};
component_tag<TSound> control_soundwave41_tag = {"soundwave41", nullptr};
component_tag<TSound> control_soundwave44_tag = {"soundwave44", nullptr};
component_tag<TSound> control_soundwave45_tag = {"soundwave45", nullptr};
component_tag<TSound> control_soundwave46_tag = {"soundwave46", nullptr};
component_tag<TSound> control_soundwave47_tag = {"soundwave47", nullptr};
component_tag<TSound> control_soundwave48_tag = {"soundwave48", nullptr};
component_tag<TSound> control_soundwave49D_tag = {"soundwave49D", nullptr};
component_tag<TSound> control_soundwave50_1_tag = {"soundwave50", nullptr};
component_tag<TSound> control_soundwave50_2_tag = {"soundwave50", nullptr};
component_tag<TSound> control_soundwave52_tag = {"soundwave52", nullptr};
component_tag<TSound> control_soundwave59_tag = {"soundwave59", nullptr};
component_tag<TPopupTarget> control_target1_tag = {"a_targ1", nullptr};
component_tag<TPopupTarget> control_target2_tag = {"a_targ2", nullptr};
component_tag<TPopupTarget> control_target3_tag = {"a_targ3", nullptr};
component_tag<TPopupTarget> control_target4_tag = {"a_targ4", nullptr};
component_tag<TPopupTarget> control_target5_tag = {"a_targ5", nullptr};
component_tag<TPopupTarget> control_target6_tag = {"a_targ6", nullptr};
component_tag<TPopupTarget> control_target7_tag = {"a_targ7", nullptr};
component_tag<TPopupTarget> control_target8_tag = {"a_targ8", nullptr};
component_tag<TPopupTarget> control_target9_tag = {"a_targ9", nullptr};
component_tag<TSoloTarget> control_target10_tag = {"a_targ10", nullptr};
component_tag<TSoloTarget> control_target11_tag = {"a_targ11", nullptr};
component_tag<TSoloTarget> control_target12_tag = {"a_targ12", nullptr};
component_tag<TSoloTarget> control_target13_tag = {"a_targ13", nullptr};
component_tag<TSoloTarget> control_target14_tag = {"a_targ14", nullptr};
component_tag<TSoloTarget> control_target15_tag = {"a_targ15", nullptr};
component_tag<TSoloTarget> control_target16_tag = {"a_targ16", nullptr};
component_tag<TSoloTarget> control_target17_tag = {"a_targ17", nullptr};
component_tag<TSoloTarget> control_target18_tag = {"a_targ18", nullptr};
component_tag<TSoloTarget> control_target19_tag = {"a_targ19", nullptr};
component_tag<TSoloTarget> control_target20_tag = {"a_targ20", nullptr};
component_tag<TSoloTarget> control_target21_tag = {"a_targ21", nullptr};
component_tag<TSoloTarget> control_target22_tag = {"a_targ22", nullptr};
component_tag<TTripwire> control_trip1_tag = {"s_trip1", nullptr};
component_tag<TTripwire> control_trip2_tag = {"s_trip2", nullptr};
component_tag<TTripwire> control_trip3_tag = {"s_trip3", nullptr};
component_tag<TTripwire> control_trip4_tag = {"s_trip4", nullptr};
component_tag<TTripwire> control_trip5_tag = {"s_trip5", nullptr};


TPinballTable* control::TableG;
component_info control::score_components[88]
{
	component_info{&control_bump1_tag, {BumperControl, 4, control_bump_scores1}},
	component_info{&control_bump2_tag, {BumperControl, 4, control_bump_scores1}},
	component_info{&control_bump3_tag, {BumperControl, 4, control_bump_scores1}},
	component_info{&control_bump4_tag, {BumperControl, 4, control_bump_scores1}},
	component_info{&control_roll3_tag, {ReentryLanesRolloverControl, 1, control_roll_scores1}},
	component_info{&control_roll2_tag, {ReentryLanesRolloverControl, 1, control_roll_scores1}},
	component_info{&control_roll1_tag, {ReentryLanesRolloverControl, 1, control_roll_scores1}},
	component_info{&control_attack_bump_tag, {BumperGroupControl, 0, nullptr}},
	component_info{&control_bump5_tag, {BumperControl, 4, control_bump_scores2}},
	component_info{&control_bump6_tag, {BumperControl, 4, control_bump_scores2}},
	component_info{&control_bump7_tag, {BumperControl, 4, control_bump_scores2}},
	component_info{&control_roll112_tag, {LaunchLanesRolloverControl, 1, control_roll_scores2}},
	component_info{&control_roll111_tag, {LaunchLanesRolloverControl, 1, control_roll_scores2}},
	component_info{&control_roll110_tag, {LaunchLanesRolloverControl, 1, control_roll_scores2}},
	component_info{&control_launch_bump_tag, {BumperGroupControl, 0, nullptr}},
	component_info{&control_rebo1_tag, {FlipperRebounderControl1, 1, control_rebo_score1}},
	component_info{&control_rebo2_tag, {FlipperRebounderControl2, 1, control_rebo_score1}},
	component_info{&control_rebo3_tag, {RebounderControl, 1, control_rebo_score1}},
	component_info{&control_rebo4_tag, {RebounderControl, 1, control_rebo_score1}},
	component_info{&control_kicker1_tag, {LeftKickerControl, 0, nullptr}},
	component_info{&control_kicker2_tag, {RightKickerControl, 0, nullptr}},
	component_info{&control_gate1_tag, {LeftKickerGateControl, 0, nullptr}},
	component_info{&control_gate2_tag, {RightKickerGateControl, 0, nullptr}},
	component_info{&control_oneway4_tag, {DeploymentChuteToEscapeChuteOneWayControl, 6, control_oneway4_score1}},
	component_info{&control_oneway10_tag, {DeploymentChuteToTableOneWayControl, 0, nullptr}},
	component_info{&control_block1_tag, {DrainBallBlockerControl, 0, nullptr}},
	component_info{&control_ramp_tag, {LaunchRampControl, 1, control_ramp_score1}},
	component_info{&control_ramp_hole_tag, {LaunchRampHoleControl, 0, nullptr}},
	component_info{&control_roll4_tag, {OutLaneRolloverControl, 1, control_roll_score1}},
	component_info{&control_roll8_tag, {OutLaneRolloverControl, 1, control_roll_score1}},
	component_info{&control_lite17_tag, {ExtraBallLightControl, 0, nullptr}},
	component_info{&control_roll6_tag, {ReturnLaneRolloverControl, 2, control_roll_score2}},
	component_info{&control_roll7_tag, {ReturnLaneRolloverControl, 2, control_roll_score2}},
	component_info{&control_roll5_tag, {BonusLaneRolloverControl, 1, control_roll_score3}},
	component_info{&control_roll179_tag, {FuelRollover1Control, 1, control_roll_score4}},
	component_info{&control_roll180_tag, {FuelRollover2Control, 1, control_roll_score4}},
	component_info{&control_roll181_tag, {FuelRollover3Control, 1, control_roll_score4}},
	component_info{&control_roll182_tag, {FuelRollover4Control, 1, control_roll_score4}},
	component_info{&control_roll183_tag, {FuelRollover5Control, 1, control_roll_score4}},
	component_info{&control_roll184_tag, {FuelRollover6Control, 1, control_roll_score4}},
	component_info{&control_flag1_tag, {FlagControl, 2, control_flag_score1}},
	component_info{&control_kickout2_tag, {HyperspaceKickOutControl, 5, control_kickout_score1}},
	component_info{&control_hyper_lights_tag, {HyperspaceLightGroupControl, 0, nullptr}},
	component_info{&control_flag2_tag, {FlagControl, 2, control_flag_score1}},
	component_info{&control_sink1_tag, {WormHoleControl, 3, control_sink_score1}},
	component_info{&control_sink2_tag, {WormHoleControl, 3, control_sink_score1}},
	component_info{&control_sink3_tag, {WormHoleControl, 3, control_sink_score1}},
	component_info{&control_flip1_tag, {LeftFlipperControl, 0, nullptr}},
	component_info{&control_flip2_tag, {RightFlipperControl, 0, nullptr}},
	component_info{&control_plunger_tag, {PlungerControl, 0, nullptr}},
	component_info{&control_target1_tag, {BoosterTargetControl, 2, control_target_score1}},
	component_info{&control_target2_tag, {BoosterTargetControl, 2, control_target_score1}},
	component_info{&control_target3_tag, {BoosterTargetControl, 2, control_target_score1}},
	component_info{&control_lite60_tag, {JackpotLightControl, 0, nullptr}},
	component_info{&control_lite59_tag, {BonusLightControl, 0, nullptr}},
	component_info{&control_target6_tag, {MedalTargetControl, 3, control_target_score2}},
	component_info{&control_target5_tag, {MedalTargetControl, 3, control_target_score2}},
	component_info{&control_target4_tag, {MedalTargetControl, 3, control_target_score2}},
	component_info{&control_bumber_target_lights_tag, {MedalLightGroupControl, 0, nullptr}},
	component_info{&control_target9_tag, {MultiplierTargetControl, 2, control_target_score3}},
	component_info{&control_target8_tag, {MultiplierTargetControl, 2, control_target_score3}},
	component_info{&control_target7_tag, {MultiplierTargetControl, 2, control_target_score3}},
	component_info{&control_top_target_lights_tag, {MultiplierLightGroupControl, 0, nullptr}},
	component_info{&control_target10_tag, {FuelSpotTargetControl, 1, control_target_score4}},
	component_info{&control_target11_tag, {FuelSpotTargetControl, 1, control_target_score4}},
	component_info{&control_target12_tag, {FuelSpotTargetControl, 1, control_target_score4}},
	component_info{&control_target13_tag, {MissionSpotTargetControl, 1, control_target_score5}},
	component_info{&control_target14_tag, {MissionSpotTargetControl, 1, control_target_score5}},
	component_info{&control_target15_tag, {MissionSpotTargetControl, 1, control_target_score5}},
	component_info{&control_target16_tag, {LeftHazardSpotTargetControl, 1, control_target_score6}},
	component_info{&control_target17_tag, {LeftHazardSpotTargetControl, 1, control_target_score6}},
	component_info{&control_target18_tag, {LeftHazardSpotTargetControl, 1, control_target_score6}},
	component_info{&control_target19_tag, {RightHazardSpotTargetControl, 1, control_target_score6}},
	component_info{&control_target20_tag, {RightHazardSpotTargetControl, 1, control_target_score6}},
	component_info{&control_target21_tag, {RightHazardSpotTargetControl, 1, control_target_score6}},
	component_info{&control_target22_tag, {WormHoleDestinationControl, 1, control_target_score7}},
	component_info{&control_roll9_tag, {SpaceWarpRolloverControl, 1, control_roll_score5}},
	component_info{&control_kickout3_tag, {BlackHoleKickoutControl, 1, control_kickout_score2}},
	component_info{&control_kickout1_tag, {GravityWellKickoutControl, 1, control_kickout_score3}},
	component_info{&control_drain_tag, {BallDrainControl, 0, nullptr}},
	component_info{&control_oneway1_tag, {SkillShotGate1Control, 0, nullptr}},
	component_info{&control_trip1_tag, {SkillShotGate2Control, 0, nullptr}},
	component_info{&control_trip2_tag, {SkillShotGate3Control, 0, nullptr}},
	component_info{&control_trip3_tag, {SkillShotGate4Control, 0, nullptr}},
	component_info{&control_trip4_tag, {SkillShotGate5Control, 0, nullptr}},
	component_info{&control_trip5_tag, {SkillShotGate6Control, 0, nullptr}},
	component_info{&control_lite200_tag, {ShootAgainLightControl, 0, nullptr}},
	component_info{&control_sink7_tag, {EscapeChuteSinkControl, 0, nullptr}},
};


component_tag_base* control::simple_components[142]
{
	&control_lite8_tag,
	&control_lite9_tag,
	&control_lite10_tag,
	&control_bmpr_inc_lights_tag,
	&control_lite171_tag,
	&control_lite170_tag,
	&control_lite169_tag,
	&control_ramp_bmpr_inc_lights_tag,
	&control_lite30_tag,
	&control_lite29_tag,
	&control_lite1_tag,
	&control_lite54_tag,
	&control_lite55_tag,
	&control_lite56_tag,
	&control_lite18_tag,
	&control_lite27_tag,
	&control_lite28_tag,
	&control_lite16_tag,
	&control_lite21_tag,
	&control_lite22_tag,
	&control_lite23_tag,
	&control_lite24_tag,
	&control_lite25_tag,
	&control_lite26_tag,
	&control_lite130_tag,
	&control_lite5_tag,
	&control_lite6_tag,
	&control_lite7_tag,
	&control_worm_hole_lights_tag,
	&control_lite4_tag,
	&control_lite2_tag,
	&control_lite3_tag,
	&control_bsink_arrow_lights_tag,
	&control_l_trek_lights_tag,
	&control_r_trek_lights_tag,
	&control_literoll179_tag,
	&control_literoll180_tag,
	&control_literoll181_tag,
	&control_literoll182_tag,
	&control_literoll183_tag,
	&control_literoll184_tag,
	&control_fuel_bargraph_tag,
	&control_lite20_tag,
	&control_lite19_tag,
	&control_lite61_tag,
	&control_lite58_tag,
	&control_lite11_tag,
	&control_lite12_tag,
	&control_lite13_tag,
	&control_lite70_tag,
	&control_lite71_tag,
	&control_lite72_tag,
	&control_top_circle_tgt_lights_tag,
	&control_lite101_tag,
	&control_lite102_tag,
	&control_lite103_tag,
	&control_ramp_tgt_lights_tag,
	&control_lite104_tag,
	&control_lite105_tag,
	&control_lite106_tag,
	&control_lite107_tag,
	&control_lite108_tag,
	&control_lite109_tag,
	&control_lchute_tgt_lights_tag,
	&control_bpr_solotgt_lights_tag,
	&control_lite110_tag,
	&control_lite62_tag,
	&control_lite67_tag,
	&control_lite68_tag,
	&control_lite69_tag,
	&control_lite131_tag,
	&control_lite132_tag,
	&control_lite133_tag,
	&control_skill_shot_lights_tag,
	&control_lite77_tag,
	&control_lite198_tag,
	&control_middle_circle_tag,
	&control_outer_circle_tag,
	&control_soundwave9_tag,
	&control_soundwave10_tag,
	&control_soundwave21_tag,
	&control_soundwave23_tag,
	&control_soundwave24_tag,
	&control_soundwave30_tag,
	&control_soundwave28_tag,
	&control_soundwave50_1_tag,
	&control_soundwave8_tag,
	&control_soundwave40_tag,
	&control_soundwave41_tag,
	&control_soundwave36_1_tag,
	&control_soundwave50_2_tag,
	&control_soundwave35_1_tag,
	&control_soundwave36_2_tag,
	&control_soundwave35_2_tag,
	&control_soundwave38_tag,
	&control_soundwave39_tag,
	&control_soundwave44_tag,
	&control_soundwave45_tag,
	&control_soundwave46_tag,
	&control_soundwave47_tag,
	&control_soundwave48_tag,
	&control_soundwave52_tag,
	&control_soundwave14_1_tag,
	&control_soundwave59_tag,
	&control_lite199_tag,
	&control_lite196_tag,
	&control_lite195_tag,
	&control_info_text_box_tag,
	&control_mission_text_box_tag,
	&control_soundwave27_tag,
	&control_lite84_tag,
	&control_lite85_tag,
	&control_soundwave14_2_tag,
	&control_soundwave3_tag,
	&control_soundwave26_tag,
	&control_soundwave49D_tag,
	&control_lite300_tag,
	&control_lite301_tag,
	&control_lite302_tag,
	&control_lite303_tag,
	&control_lite304_tag,
	&control_lite305_tag,
	&control_lite306_tag,
	&control_lite307_tag,
	&control_lite308_tag,
	&control_lite309_tag,
	&control_lite310_tag,
	&control_lite311_tag,
	&control_lite312_tag,
	&control_lite313_tag,
	&control_lite314_tag,
	&control_lite315_tag,
	&control_lite316_tag,
	&control_lite317_tag,
	&control_lite318_tag,
	&control_lite319_tag,
	&control_lite320_tag,
	&control_lite321_tag,
	&control_lite322_tag,
	&control_goal_lights_tag,
	&control_soundwave25_tag,
	&control_soundwave7_tag
};

int control::waiting_deployment_flag;
bool control::table_unlimited_balls = false;
int control::extraball_light_flag;
int control::RankRcArray[9] = {84, 85, 86, 87, 88, 89, 90, 91, 92};
int control::MissionRcArray[17] = {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76};
int control::mission_select_scores[17] =
{
	10000,
	10000,
	10000,
	10000,
	20000,
	20000,
	20000,
	20000,
	20000,
	20000,
	20000,
	20000,
	20000,
	30000,
	30000,
	30000,
	30000
};
component_tag_base* control::wormhole_tag_array1[3] =
{
	&control_sink1_tag, &control_sink2_tag, &control_sink3_tag
};

component_tag_base* control::wormhole_tag_array2[3] =
{
	&control_lite5_tag, &control_lite6_tag, &control_lite7_tag
};

component_tag_base* control::wormhole_tag_array3[3] =
{
	&control_lite4_tag, &control_lite2_tag, &control_lite3_tag
};


void control::make_links(TPinballTable* table)
{
	TableG = table;

	for (int index = 0; index < 88; index++)
	{
		auto compPtr = &score_components[index];
		TPinballComponent* comp = make_component_link(compPtr->Tag);
		if (comp)
		{
			comp->Control = &compPtr->Control;
			for (int scoreId = 0; scoreId < compPtr->Control.ScoreCount; scoreId++)
			{
				comp->put_scoring(scoreId, compPtr->Control.Scores[scoreId]);
			}
		}
	}

	for (int i = 0; i < 142; ++i)
		make_component_link(simple_components[i]);
}

void control::ClearLinks()
{
	TableG = nullptr;
	for (auto& component : score_components)
		component.Tag->SetComponent(nullptr);
	for (auto& component : simple_components)
		component->SetComponent(nullptr);
}

TPinballComponent* control::make_component_link(component_tag_base* tag)
{
	if (tag->GetComponent())
		return tag->GetComponent();

	for (auto component: TableG->ComponentList)
	{
		if (component->GroupName)
		{
			if (!strcmp(component->GroupName, tag->Name))
			{
				tag->SetComponent(component);
				return component;
			}
		}
	}

	return nullptr;
}

namespace
{
	// Rules for the Full Tilt tables other than Space Cadet. Every component's score values come from the data
	// tables of the original game executables (lenient_scores.h); jackpots, bonuses and the quests / modes follow
	// the table rules of the original help file. The handler code of the original is not ported, so the quest
	// flow is a reconstruction from those rules.
	enum { JACKPOT = -1, EXTRA_BALL = -2, MYSTERY = -3, MAX_WEAPONS = -4, MAX_ARMOR = -5 };
	typedef const char* const* Roles; // null terminated; a trailing '*' matches a name prefix

	struct Quest
	{
		const char* name;
		Roles roles;       // components that count towards the quest
		int goal;
		int awards[6];     // award for the 1st, 2nd... hit (last one repeats): points, JACKPOT or EXTRA_BALL
		int jackpotEvery;  // also award the jackpot on every nth hit (0 = never)
		int jackpotAdd;    // added to the jackpot on every hit
		int startPoints;   // paid when the mode starts (0 = the profile's start points)
	};

	struct Profile
	{
		const ComponentScore* scores;
		int scoreCount;
		int jackpotStart, jackpotTarget, jackpotSink, jackpotQuest;
		Roles startRoles;
		int startHits, startPoints;
		const char* startText;
		int bonusPerTarget, bonusPerQuest;
		const char* questWord;
		Roles targets, sinks;
		int questCount;
		Quest quests[8];
		const char* selectTarget;
	};

	const char* const DragonStart[] = {"a_sink1", "a_sink2", nullptr};
	const char* const DragonTargets[] = {"a_spot*", nullptr};
	const char* const DragonSinks[] = {"a_sink*", "a_kout*", nullptr};
	const char* const FireLizards[] = {"a_sink1", "a_sink2", nullptr};
	const char* const PrisonTower[] = {"s_trip5", "s_trip6", nullptr};
	const char* const Kickouts[] = {"a_kout*", "a_sink19", nullptr};
	const char* const Well[] = {"a_sink4", nullptr};
	const char* const Gems[] = {"a_spot*", "a_bump*", nullptr};

	const Profile Dragon = {
		DragonScores, sizeof DragonScores / sizeof DragonScores[0],
		1000000, 50000, 75000, 500000,
		DragonStart, 2, 100000, "Hit fire lizard sinks to begin quest",
		2000, 100000, "Quest", DragonTargets, DragonSinks, 5,
		{
			// The quest order of the original: its quest numbers 4 to 8 select the messages Dragon Hoard, Fire Lizards, Rescue Maiden,
			// Dragon Pass and Wizard's Fury
			{"Dragon Hoard: steal the gems", Gems, 9999, {50000, 60000, 70000, 100000, 200000, 250000}, 0, 0},
			{"Fire Lizard Attack: hit the sinks", FireLizards, 9999, {100000, 200000, 300000, 400000, 500000, 1000000}, 0, 0},
			{"Rescue Maiden: prison tower", PrisonTower, 9999, {250000, 500000, JACKPOT, EXTRA_BALL, 0, 0}, 0, 0},
			{"Dragon Pass: hit the kickouts", Kickouts, 9999, {100000, 100000, 100000, 100000, JACKPOT, 0}, 0, 250000},
			{"Wizard's Fury: put the ball in the well", Well, 9999, {MYSTERY, MYSTERY, MYSTERY, MYSTERY, MYSTERY, MYSTERY}, 0, 0},
		},
		"a_spot27"
	};

	const char* const PirateStart[] = {"a_drop*", "a_spot*", nullptr};
	const char* const PirateTargets[] = {"a_drop*", "a_spot*", nullptr};
	const char* const PirateSinks[] = {"a_sink*", nullptr};
	const char* const ShipTargets[] = {"a_drop5", "a_drop6", "a_drop7", "a_drop8", "a_drop9", nullptr};
	const char* const Hideaways[] = {"a_sink17", "a_sink15", "a_sink14", "a_sink9", "a_sink12", nullptr};
	// The routes with a combo of their own: the island ramps and the orbit sensors (0x428b70, 0x428d80, 0x429210, 0x429400)
	const char* const IslandRoutes[] = {"a_ramp8", "a_ramp5", "s_trip3", "s_trip8", nullptr};
	const char* const WindLanes[] = {"a_roll2", "a_roll9", "a_roll8", "a_roll6", nullptr};
	const char* const TavernParts[] = {"a_drop13", "a_drop14", "a_drop15", "a_sink5", "a_sink6", "a_sink7", nullptr};
	const char* const ParrotVolcano[] = {"a_drop10", "a_drop11", "a_drop12", "a_spot8", "a_spot9", "a_spot10", "a_spot11", nullptr};
	const char* const Bumpers[] = {"a_bump*", nullptr};
	const char* const DropTargets[] = {"a_drop*", nullptr};

	const Profile Pirates = {
		PirateScores, sizeof PirateScores / sizeof PirateScores[0],
		1000000, 20000, 40000, 750000,
		PirateStart, 10, 200000, "Hit targets to spell SKULDUGGERY",
		10000, 200000, "Mode", PirateTargets, PirateSinks, 7,
		{
			// The order of the original: its mode messages are Attack, Treasure Hunt, Tavern, Bermuda, Storm, Mutiny, Swordfight
			{"Attack Ship: hit the ship targets", ShipTargets, 9999, {10000, 10000, 10000, 10000, JACKPOT, 0}, 0, 25000, 200000},
			{"Treasure Hunt: find the hideaways", Hideaways, 5, {100000, 250000, 500000, 750000, JACKPOT, 0}, 0, 0, 300000},
			{"Tavern: hit targets and sinks", TavernParts, 6, {25000, 25000, 25000, 25000, 25000, JACKPOT}, 0, 50000, 200000},
			{"Bermuda Triangle: take the wind lanes", WindLanes, 9999, {125000, 250000, 500000, 1000000, JACKPOT, 0}, 0, 0, 200000},
			// Storm: any drop target bails water (type 1006 events in the original); value and jackpot interval follow the storm level
			{"Storm: bail the water", DropTargets, 9999, {25000, 25000, 25000, 25000, 25000, 25000}, 7, 0, 300000},
			{"Mutiny: hit the bumpers", Bumpers, 10, {25000, 25000, 25000, 25000, 25000, 25000}, 10, 0, 100000},
			{"Swordfight: parrot and volcano targets", ParrotVolcano, 7, {30000, 30000, 30000, 30000, 30000, 30000}, 0, 0, 250000},
		},
		"a_spot102"
	};

	const Profile* Rules = &Dragon;
	int Jackpot, QuestIndex, QuestHits, QuestsDone, StartHits, TargetsHit;
	bool QuestActive, LastBallLost;
	unsigned LaunchTicks;
	int Hits[128];       // hits per score entry this ball
	// Skulduggery routes (ramps, orbit sensors and wind lanes): lights lit by each hit give the score step
	int RouteCombo[128], RouteLights[128], LastRoute = -1;
	bool BankPaid[128];  // bank bonus already awarded this ball
	int ForestHits; // Dragon's Keep: forest bumper hits this ball; every tenth gives a weapon (a_bump1 field of the original)
	int BumperHits, Weapons, SwordHits, SlayHits, SlayNeed, SuperJackpot, BonusHold;
	bool BonusHoldLit;
	bool SlayActive;
	unsigned SlayEnd;
	char Line[96];
	// Dragon's Keep quest flow of the original code: the next quest is drawn at random from the quests not completed
	// yet, the quest selection target draws again, a quest that has ended can be restarted for ten seconds, and
	// completing all of them starts the slay dragon quest. Wizard's Fury pays the mystery award the spell targets set.
	bool QuestDone[8];
	int Armor, Mystery, MysteryIdx, Treasures, Eggs, LoopCount, MenuTier;
	unsigned LoopTime, MenuEnd;
	// Multiball (Dragon's Keep): balls on the table, the running mode, the dragon letters and the tower lock
	int BallsInPlay, MultiMode, LetterMask, FireMask, TowerMask, GargoyleMask;
	bool LockLit;
	enum { MULTI_NONE, MULTI_GAGGLE, MULTI_BARRAGE, MULTI_FLURRY };
	bool MenuOpen, ExtraBallLight;
	int Spells, SpellMask, SpellsCast, Offense, Defense;
	bool FirstHit; // the next component hit after a launch decides the skill shot
	int LaneMask, WindHits, StormEvery, StormValue, Coins, MapPieces, ParrotMask, VolcanoMask;
	int LavaMask; // idle state: the volcano lights that start Lava-Ball when all four are lit
	int Spot6Hits; // Skulduggery idle state: the hits on a_spot6 (original 0x4279b0); the third starts Jail Break
	int PirateLetters; // SKULDUGGERY: the letters lit so far in the idle state
	int HeldBalls; // Jail: balls held in the brig (original DAT_00435d3c); the third trap starts Jail Break
	// Quest and mode lengths in seconds, from the timers the original code sets for each
	const float DragonSeconds[] = {27.73f, 31.69f, 30.45f, 30.65f, 30.69f};
	const float PirateSeconds[] = {30.0f, 30.68f, 27.4f, 31.14f, 24.14f, 30.0f, 30.0f};
	unsigned ModeStart;
	int BermudaCount;
	int BuriedCoins, BuriedSpecial, BuriedBonus, BuriedJackpot; // Treasure Hunt: finds that are paid when the mode ends
	int Fathom, IslandMask; // Skulduggery: fathom level 1..7 (original player +0x15e), the island lane lights (two per lane)
	bool BuriedExtra, ShipMystery; // ShipMystery: the shipwreck mystery waits on the rollover a_roll3
	int HoardMask, TreasureX; // Treasure Hunt: the hideaway where the X is flashing
	unsigned ModeEnd; // Skulduggery modes are timed (about 30 seconds in the original); the captive ball adds ten
	bool LootActive; // Skulduggery: every mode done, the ship sink finds Peg Leg's loot
	unsigned RestartEnd;
	int RestartQuest;
	const char* const SpellTargets[] = {"a_spot4", "a_spot5", "a_spot6", "a_spot7", "a_spot22"};
	// Mystery award per spell target, from the original handlers (state 8): extra ball, max weapons, max armor, jackpot, one million
	const int SpellAwards[] = {EXTRA_BALL, MAX_WEAPONS, MAX_ARMOR, JACKPOT, 1000000};

	bool match(Roles roles, const char* name)
	{
		for (; *roles; ++roles)
		{
			size_t n = strlen(*roles);
			if ((*roles)[n - 1] == '*' ? !strncmp(*roles, name, n - 1) : !strcmp(*roles, name))
				return true;
		}
		return false;
	}

	void say(TTextBox* box, const char* text, float time, int type)
	{
		if (box)
			box->Display(text, time, type);
	}

	void show_quest()
	{
		const Quest& q = Rules->quests[QuestIndex];
		if (LootActive)
			snprintf(Line, sizeof Line, "Hit X to find Peg Leg's Loot");
		else if (QuestActive)
			snprintf(Line, sizeof Line, "%s (%d/%d)", q.name, QuestHits, q.goal);
		else
			snprintf(Line, sizeof Line, "%s", Rules->startText);
		say(pinball::MissTextBox, Line, -1.0f, 1);
	}

	void award(int value)
	{
		if (value == JACKPOT)
		{
			if (Jackpot > 10000000)
				Jackpot = 10000000;
			pb::MainTable->AddScore(Jackpot);
			snprintf(Line, sizeof Line, "Jackpot %d", Jackpot);
			say(pinball::InfoTextBox, Line, 3.0f, 2);
		}
		else if (value == EXTRA_BALL)
		{
			++pb::MainTable->ExtraBalls;
			say(pinball::InfoTextBox, "Extra Ball", 3.0f, 2);
		}
		else if (value == MYSTERY)
		{
			award(Mystery);
			// After the well pays, the mystery award changes to another one at random
			int next = rand() % 4;
			MysteryIdx = next >= MysteryIdx ? next + 1 : next;
			Mystery = SpellAwards[MysteryIdx];
		}
		else if (value == MAX_WEAPONS)
		{
			Weapons = 4;
			say(pinball::InfoTextBox, "Max Weapons", 3.0f, 2);
		}
		else if (value == MAX_ARMOR)
		{
			Armor = 3;
			say(pinball::InfoTextBox, "Max Armor", 3.0f, 2);
		}
		else if (value > 0)
			pb::MainTable->AddScore(value);
	}

	// The next quest: any of the quests not completed yet (-1 when there are none left)
	int draw_quest(int avoid)
	{
		int open[8], count = 0;
		for (int i = 0; i < Rules->questCount; ++i)
			if (!QuestDone[i] && i != avoid)
				open[count++] = i;
		if (!count && avoid >= 0 && !QuestDone[avoid])
			return avoid;
		return count ? open[rand() % count] : -1;
	}

	// Coin awards (50,000 doubling), special treasures and the six map pieces of Skulduggery
	void coin_award()
	{
		static const int coin[] = {50000, 100000, 200000, 400000, 800000, 1600000};
		pb::MainTable->AddScore(coin[Coins < 5 ? Coins : 5]);
		if (Coins < 6)
			++Coins;
		say(pinball::InfoTextBox, "Coin Award", 3.0f, 2);
	}

	// Special treasures in the order of the original: gold ingots, silver chalice, signet ring, Frantz ruby, sceptre, crown
	void special_treasure()
	{
		static const int treasure[] = {100000, 250000, 500000, 750000, 1000000, 1500000};
		static const char* const names[] = {"Gold Ingots", "Silver Chalice", "Signet Ring", "Frantz Ruby", "Sceptre", "Crown of Sandige"};
		int n = Treasures < 5 ? Treasures : 5;
		pb::MainTable->AddScore(treasure[n]);
		++Treasures;
		say(pinball::InfoTextBox, names[n], 3.0f, 2);
	}

	void map_piece()
	{
		pb::MainTable->AddScore(1000000);
		if (MapPieces < 6)
			++MapPieces;
		snprintf(Line, sizeof Line, "Map Piece %d", MapPieces);
		say(pinball::InfoTextBox, Line, 3.0f, 2);
	}

	// Dragon's Keep tower diverters: four pairs of one-way gates (original: messages 0x3e and 0x3f to a_dvtraa/b, ba/bb, ca/cb,
	// da/db). Message 0x3f makes a gate active and 0x3e inactive (the gate class of the original, 0x415410): position 1 sends
	// 0x3e to the first gate and 0x3f to the second, position 2 the opposite
	void diverter(int pair, int position)
	{
		static const char* const gates[4][2] = {{"a_dvtraa", "a_dvtrab"}, {"a_dvtrba", "a_dvtrbb"}, {"a_dvtrca", "a_dvtrcb"}, {"a_dvtrda", "a_dvtrdb"}};
		auto first = pb::MainTable->find_component(gates[pair][0]);
		auto second = pb::MainTable->find_component(gates[pair][1]);
		if (first)
			first->Message(position == 1 ? 62 : 63, 0.0f);
		if (second)
			second->Message(position == 1 ? 63 : 62, 0.0f);
	}

	// Info states 6 (the Rescue Maiden quest, "Put ball in Prison Tower") and 0xd (Tower Barrage) of the original: the
	// diverter handlers leave pairs A and D as they are
	bool tower_busy()
	{
		return (Rules == &Dragon && QuestActive && QuestIndex == 2) || MultiMode == MULTI_BARRAGE;
	}

	// The diverters at the start of a ball (original 0x4245b0)
	void reset_diverters()
	{
		if (Rules != &Dragon)
			return;
		if (!tower_busy())
		{
			diverter(0, 2);
			diverter(3, 2);
		}
		diverter(1, 1);
		diverter(2, 1);
	}

	// The idle state of Skulduggery (info state 2): no mode, no loot and no extra balls from Lava-Ball or Jail Break
	bool pirate_idle()
	{
		return !QuestActive && !LootActive && BallsInPlay <= 1;
	}

	// Peg Leg's Loot starts from every path that sets it, and pays its start amount (0x42cfc0, 0x4f)
	void start_loot()
	{
		LootActive = true;
		pb::MainTable->AddScore(1000000);
	}

	// original 0x424350 / 0x4243d0: one more fathom light, up to six (fathom level seven)
	void fathom_up()
	{
		if (Fathom < 7)
			++Fathom;
	}

	// original 0x425c50: the shipwreck mystery is one of six awards
	void shipwreck_mystery()
	{
		ShipMystery = false;
		switch (rand() % 6)
		{
		case 0: special_treasure(); break;
		case 1: award(EXTRA_BALL); break;
		case 2:
			{
				// Max Crew (original 0x425000): the bumpers go to the top level, twelve hits per level (see component_score)
				if (BumperHits < 72) BumperHits = 72;
				int value = 0;
				for (int i = 0; i < Rules->scoreCount; ++i)
				{
					const ComponentScore& s = Rules->scores[i];
					if (!strncmp(s.name, "a_bump", 6))
					{
						value = s.values[6 < s.count ? 6 : s.count - 1];
						break;
					}
				}
				snprintf(Line, sizeof Line, "Max Crew\nBumpers Now %d", value);
				say(pinball::InfoTextBox, Line, 3.0f, 2);
			}
			break;
		case 3:
			fathom_up();
			say(pinball::InfoTextBox, "Fathoms Up", 3.0f, 2);
			break;
		case 4: map_piece(); break;
		default: coin_award();
		}
	}

	// The random award of the original (FUN_00424fb0): map piece, special treasure, coin award or extra ball, equally likely
	void random_award()
	{
		switch (rand() % 4)
		{
		case 0: coin_award(); break;
		case 1: special_treasure(); break;
		case 2: map_piece(); break;
		default: award(EXTRA_BALL); break;
		}
		if (MapPieces >= 6 && !LootActive)
			start_loot();
	}

	// Casting a spell pays 120,000 and counts for the 75,000 per spell in the ball bonus (FUN_004236b0 of the original)
	// There are four spells, each cast once: two offensive ones (fewer dragon hits needed) and two defensive ones (more time).
	// A random one of those not cast yet is chosen; when all are cast nothing happens.
	void cast_spell()
	{
		int open[4], count = 0;
		for (int i = 0; i < 4; ++i)
			if (!(SpellsCast & (1 << i)))
				open[count++] = i;
		if (!count)
			return;
		int spell = open[rand() % count];
		SpellsCast |= 1 << spell;
		++Spells;
		if (spell < 2)
			++Offense;
		else
			++Defense;
		pb::MainTable->AddScore(120000);
		say(pinball::InfoTextBox, "Spell Cast", 3.0f, 2);
	}

	// A new ball is put on the plunger and fired up the launch lane
	std::vector<int> PendingFeeds;
	TPinballComponent* LockedSinks[3];
	int Locked;

	void FeedTimer(int id, void*)
	{
		TPinballTable* table = pb::MainTable;
		if (!table || !table->Plunger)
			return;
		for (auto it = PendingFeeds.begin(); it != PendingFeeds.end(); ++it)
			if (*it == id)
			{
				PendingFeeds.erase(it);
				break;
			}
		TBall* ball = TPlunger::FreeBall(table);
		if (!ball)
			return;
		ball->Message(1024, 0.0f);
		ball->Position.X = table->PlungerPositionX;
		ball->Position.Y = table->PlungerPositionY;
		ball->Position.Z = ball->Offset;
		ball->ActiveFlag = 1;
		table->Plunger->Message(1017, 0.0f);
	}

	// Ball over: cancel the feeds still queued and let the balls locked in the tower sinks out
	void end_multiball_state()
	{
		for (int id : PendingFeeds)
			timer::kill(id);
		PendingFeeds.clear();
		for (int i = 0; i < Locked; ++i)
			LockedSinks[i]->Message(1024, 0.0f);
		Locked = 0;
	}

	void feed_balls(int count)
	{
		for (int i = 0; i < count; ++i)
			PendingFeeds.push_back(timer::set(1.0f + 1.5f * i, nullptr, FeedTimer));
		BallsInPlay += count;
	}

	// Gargoyle Gaggle-Ball (two balls), Tower Barrage (three, the locked balls) and Dragon Flurry (five)
	void start_multiball(int mode, int extraBalls, const char* text)
	{
		MultiMode = mode;
		if (mode == MULTI_GAGGLE)
			pb::MainTable->AddScore(100000); // only Gaggle (0x42b3c0) pays at the start; Barrage and Flurry do not
		say(pinball::InfoTextBox, text, 3.0f, 2);
		// original 0x42b3c0: the Gaggle ball comes out of the sink a_sink1
		auto sink = mode == MULTI_GAGGLE ? dynamic_cast<TSink*>(pb::MainTable->find_component("a_sink1")) : nullptr;
		if (sink && !sink->HeldBall && !sink->SpawnBall)
		{
			sink->SpawnBall = true;
			sink->Message(56, -1.0f);
			--extraBalls;
			++BallsInPlay;
		}
		feed_balls(extraBalls);
	}

	// A ball drained while others are still on the table; the mode ends with one ball left
	void extra_ball_lost()
	{
		if (BallsInPlay > 1)
			--BallsInPlay;
		if (BallsInPlay <= 1 && MultiMode)
		{
			MultiMode = MULTI_NONE;
			show_quest();
		}
	}

	// The six dragon letter lights; all lit start Dragon Flurry
	void dragon_letter(int bit)
	{
		// the handlers of the original (0x4265e0, 0x426740, 0x424d20 and the others) light a letter only in the idle state
		if (QuestActive || SlayActive || MultiMode)
			return;
		LetterMask |= 1 << bit;
		if (LetterMask == 63)
		{
			LetterMask = 0;
			start_multiball(MULTI_FLURRY, 4, "Dragon Flurry");
		}
	}

	// Tower lock: after the tower targets, the tower sinks a_sink18, a_sink17 and a_sink16 lock a ball each (a new one is
	// fed); the third lock starts Tower Barrage with the three locked balls. Returns true when the ball stays locked.
	bool lock_ball(TPinballComponent* cmp)
	{
		// Each lock light has two sinks that trap a ball (original handlers 0x426f90 and 0x427100 for v_lite48, 0x4273d0 and
		// 0x427290 for v_lite49, 0x4274d0 and 0x427680 for v_lite50); the diverters choose between them
		static const char* const locks[3][2] = {{"a_sink18", "a_sink15"}, {"a_sink17", "a_sink13"}, {"a_sink9", "a_sink10"}};
		if (Rules != &Dragon || !LockLit || MultiMode || Locked >= 3 || !cmp->GroupName
			|| (strcmp(cmp->GroupName, locks[Locked][0]) && strcmp(cmp->GroupName, locks[Locked][1])))
			return false;
		LockedSinks[Locked++] = cmp;
		if (Locked < 3)
		{
			// original 0xbc2 "Ball Trapped\n%ld" shows the sink's score
			auto sink = dynamic_cast<TSink*>(cmp);
			snprintf(Line, sizeof Line, "Ball Trapped\n%d", sink ? sink->get_scoring(0) : 0);
			say(pinball::InfoTextBox, Line, 2.0f, 2);
			feed_balls(1);
			return true;
		}
		// Tower Barrage: the towers kick their balls out one after the other
		Locked = 0;
		LockLit = false;
		MultiMode = MULTI_BARRAGE;
		say(pinball::InfoTextBox, "Tower Barrage", 3.0f, 2);
		for (int i = 0; i < 3; ++i)
			LockedSinks[i]->Message(56, 1.0f + i);
		return true;
	}

	void start_slay()
	{
		SlayActive = true;
		SlayHits = 0;
		// Hits needed: eight minus the weapons and offensive spells; time: 30 seconds plus five per armor piece and defensive spell
		SlayNeed = 8 - Weapons - Offense < 2 ? 2 : 8 - Weapons - Offense;
		SlayEnd = SDL_GetTicks() + 30000 + 5000 * (Armor + Defense);
		pb::MainTable->AddScore(500000);
		snprintf(Line, sizeof Line, "Slay Dragon: ball in the dragon's mouth (%d)", SlayNeed);
		say(pinball::MissTextBox, Line, -1.0f, 1);
	}

	void new_game()
	{
		Rules = winmain::DatFileName == "PIRATES.DAT" ? &Pirates : &Dragon;
		Jackpot = Rules->jackpotStart;
		reset_diverters();
		memset(QuestDone, 0, sizeof QuestDone);
		Armor = RestartQuest = Treasures = Eggs = Spells = SpellMask = SpellsCast = Offense = Defense = LoopCount = MenuTier = 0;
		LoopTime = MenuEnd = 0;
		MenuOpen = ExtraBallLight = false;
		end_multiball_state();
		BallsInPlay = 1;
		MultiMode = LetterMask = FireMask = TowerMask = GargoyleMask = SwordHits = 0;
		LockLit = false;
		FirstHit = false;
		LootActive = false;
		ModeEnd = 0;
		LaneMask = WindHits = Coins = MapPieces = LavaMask = HeldBalls = PirateLetters = Spot6Hits = 0;
		RestartEnd = 0;
		Mystery = 1000000;
		MysteryIdx = 4;
		QuestIndex = QuestHits = QuestsDone = StartHits = TargetsHit = BumperHits = ForestHits = Weapons = SwordHits = SlayHits = SlayNeed = 0;
		SuperJackpot = 2500000;
		BonusHold = 0;
		BonusHoldLit = false;
		Fathom = 1;
		IslandMask = 0;
		ShipMystery = false;
		SlayActive = false;
		QuestActive = LastBallLost = false;
		LaunchTicks = 0;
		QuestIndex = draw_quest(-1);
		memset(Hits, 0, sizeof Hits);
		memset(RouteCombo, 0, sizeof RouteCombo);
		memset(RouteLights, 0, sizeof RouteLights);
		LastRoute = -1;
		memset(BankPaid, 0, sizeof BankPaid);
	}

	// The component's own score: flat, stepping up per hit, or a per hit value plus a bank bonus
	int component_score(int index)
	{
		const ComponentScore& s = Rules->scores[index];
		int hits = Hits[index]++;
		if (Rules == &Pirates && (match(WindLanes, s.name) || match(IslandRoutes, s.name)))
		{
			// original 0x428b70 and its siblings: a hit lights the next light of the route's group (the light stays on, only
			// its flashing lasts two seconds), and the lit count before the hit is the score step. The ramps and orbit
			// sensors also light a combo group, which another route scoring puts out (0x4232c0). The route lights light only
			// in the idle state and start again with each ball and each ended mode (0x42c070, cases 0x4f and 0x52).
			if (LastRoute >= 0 && LastRoute != index) RouteCombo[LastRoute] = 0;
			LastRoute = index;
			int step = RouteLights[index] < 2 ? RouteLights[index] : 2;
			if (match(IslandRoutes, s.name))
			{
				step += (RouteCombo[index] < 3 ? RouteCombo[index] : 3) * 3;
				++RouteCombo[index];
			}
			if (pirate_idle())
				++RouteLights[index];
			return s.values[step];
		}
		if (s.count == 1)
			return s.values[0];
		if (!strncmp(s.name, "a_bump", 6))
		{
			int step = BumperHits++ / 12;
			if (Rules == &Pirates && BumperHits % 12 == 0 && step < 6)
			{
				// Every twelve bumper hits add crew: the bumpers are worth more
				snprintf(Line, sizeof Line, "Crew Added Bumpers Now %d", Rules->scores[index].values[step + 1]);
				say(pinball::InfoTextBox, Line, 2.0f, 2);
			}
			return s.values[step < s.count ? step : s.count - 1];
		}
		int group = 0, done = 0;
		for (int i = 0; i < Rules->scoreCount; ++i)
		{
			const ComponentScore& o = Rules->scores[i];
			if (o.count == s.count && !memcmp(o.values, s.values, sizeof(int) * s.count))
			{
				++group;
				if (Hits[i] > 0)
					++done;
			}
		}
		if (s.count == 2 && group >= 2)
		{
			int value = s.values[0];
			if (done == group && !BankPaid[index])
			{
				for (int i = 0; i < Rules->scoreCount; ++i)
					if (!memcmp(Rules->scores[i].values, s.values, sizeof(int) * 2) && Rules->scores[i].count == 2)
						BankPaid[i] = true;
				value += s.values[1];
			}
			return value;
		}
		return s.values[hits < s.count ? hits : s.count - 1];
	}

	// The super jackpot grows with every component hit; the sword target starts the slay dragon quest on its third
	// hit, which needs the ball in the dragon's mouth (a_sink19, from the original handler; a_kout3 only sets a flag) as often as eight minus the weapons won, in 30 seconds
	void dragon_slay(const char* name)
	{
		if (!strncmp(name, "a_bump", 6)) SuperJackpot += 50000;
		else if (!strncmp(name, "a_spot", 6)) SuperJackpot += 100000;
		else if (!strcmp(name, "a_sink1") || !strcmp(name, "a_sink2")) SuperJackpot += 500000;
		else if (!strncmp(name, "a_kout", 6)) SuperJackpot += 750000;
		if (SuperJackpot > 20000000) SuperJackpot = 20000000;

		if (!SlayActive)
		{
			// original 0x425750/0x4257c0/0x425830, idle state only: the sword targets must be hit in order, a_spot19, a_spot26,
			// then a_spot28, which starts the slay
			static const char* const sword[] = {"a_spot19", "a_spot26", "a_spot28"};
			if (!QuestActive && !MultiMode && !strcmp(name, sword[SwordHits]) && ++SwordHits == 3)
			{
				SwordHits = 0;
				start_slay();
			}
			return;
		}
		if (SDL_GetTicks() > SlayEnd)
		{
			SlayActive = false;
			say(pinball::InfoTextBox, "The dragon escapes", 3.0f, 2);
			show_quest();
			return;
		}
		if (strcmp(name, "a_sink19"))
			return;
		// original 0x427f10: the award depends on how many lights of the sweeping dragon fire are lit
		// (it climbs 9 lights, quickly over the last three, and goes down again)
		static const double step[9] = {0.123, 0.123, 0.123, 0.123, 0.123, 0.123, 0.012, 0.012, 0.012};
		double t = fmod(SDL_GetTicks() / 1000.0, 2 * (6 * 0.123 + 3 * 0.012));
		int lit = 9;
		bool up = true;
		for (int pass = 0; pass < 2; ++pass, up = false)
		{
			bool found = false;
			for (int i = 0; i < 9 && !found; ++i)
			{
				double d = step[up ? i : 8 - i];
				if (t < d)
				{
					lit = up ? i + 1 : 8 - i;
					found = true;
				}
				else
					t -= d;
			}
			if (found)
				break;
		}
		SlayHits++;
		if (lit == 2)
			award(1000000);
		else if (lit == 3 && rand() % 5 == 0)
			award(JACKPOT);
		else if (lit >= 4 && rand() % 10 == 0)
		{
			if (lit == 4)
			{
				ExtraBallLight = true;
				say(pinball::InfoTextBox, "Extra Ball Light", 2.0f, 2);
			}
			else
				award(EXTRA_BALL);
		}
		else
			award(100000);
		if (SlayHits < SlayNeed)
		{
			SlayEnd += 15000; // original 0x427f10: every ball in the mouth adds 15 seconds
			// original 0x427f10: one of six sinks, chosen at random, is told to release its ball after three seconds; a ball
			// held by a tower lock stays locked here, so the lock order of the port is kept
			static const char* const sinks[] = {"a_sink4", "a_sink1", "a_sink2", "a_sink18", "a_sink17", "a_sink16"};
			const char* pick = sinks[rand() % 6];
			bool locked = false;
			for (int i = 0; i < Locked; ++i)
				if (LockedSinks[i] && LockedSinks[i]->GroupName && !strcmp(LockedSinks[i]->GroupName, pick))
					locked = true;
			if (!locked)
				if (auto sink = pb::MainTable->find_component(pick))
					sink->Message(56, 3.0f);
			snprintf(Line, sizeof Line, "Slay Dragon: %d hits left", SlayNeed - SlayHits);
			say(pinball::MissTextBox, Line, -1.0f, 1);
			return;
		}
		SlayActive = false;
		BonusHoldLit = true; // slaying the dragon lights the bonus hold (v_lite31)
		++QuestsDone;
		// original 0x42a150: the super jackpot, then 1,500,000 and the jackpot (0x424490)
		pb::MainTable->AddScore(SuperJackpot);
		pb::MainTable->AddScore(1500000);
		pb::MainTable->AddScore(Jackpot);
		snprintf(Line, sizeof Line, "Super Jackpot %d", SuperJackpot);
		say(pinball::InfoTextBox, Line, 5.0f, 2);
		show_quest();
	}

	// The sounds the original code of this component plays when it is hit
	void play_sounds(const char* component)
	{
		const SoundOp* ops = Rules == &Pirates ? PirateSounds : DragonSounds;
		size_t count = Rules == &Pirates ? sizeof PirateSounds / sizeof PirateSounds[0] : sizeof DragonSounds / sizeof DragonSounds[0];
		for (size_t i = 0; i < count; ++i)
		{
			if (strcmp(ops[i].component, component))
				continue;
			auto sound = dynamic_cast<TSound*>(pb::MainTable->find_component(ops[i].sound));
			if (sound)
				sound->Play();
		}
	}

	// The lights the original code of this component switches on or makes flash
	void apply_lights(const char* component)
	{
		const LightOp* ops = Rules == &Pirates ? PirateLights : DragonLights;
		size_t count = Rules == &Pirates ? sizeof PirateLights / sizeof PirateLights[0] : sizeof DragonLights / sizeof DragonLights[0];
		for (size_t i = 0; i < count; ++i)
		{
			if (strcmp(ops[i].component, component))
				continue;
			TPinballComponent* light = pb::MainTable->find_component(ops[i].light);
			if (light)
				light->Message(ops[i].code, ops[i].value);
		}
	}

	// A quest or mode ends when its timer runs out (or its goal is met). The original credits it either way: the jackpot
	// grows, the quest light stays lit and the next quest is drawn.
	void end_quest()
	{
		if (Rules == &Pirates)
		{
			// the route lights start again when a mode ends (0x42c070 case 0x52)
			memset(RouteCombo, 0, sizeof RouteCombo);
			memset(RouteLights, 0, sizeof RouteLights);
		}
		if (Rules == &Pirates && QuestIndex == 1)
		{
			// original 0x425ab0: pay what was buried
			for (; BuriedCoins > 0; --BuriedCoins) coin_award();
			for (; BuriedSpecial > 0; --BuriedSpecial) special_treasure();
			if (BuriedBonus) pb::MainTable->AddScore(BuriedBonus);
			if (BuriedJackpot) pb::MainTable->AddScore(BuriedJackpot);
			if (BuriedExtra) award(EXTRA_BALL);
			BuriedBonus = BuriedJackpot = 0;
			BuriedExtra = false;
		}
		QuestActive = false;
		QuestHits = 0;
		++QuestsDone;
		Jackpot += Rules->jackpotQuest;
		snprintf(Line, sizeof Line, "%s over", Rules->questWord);
		say(pinball::InfoTextBox, Line, 4.0f, 2);
		if (Rules == &Dragon)
		{
			// Completed quests drop out of the draw; with none left the dragon can be slain. The quest can be restarted
			// by a fire lizard sink for the next ten seconds.
			QuestDone[QuestIndex] = true;
			RestartQuest = QuestIndex;
			RestartEnd = SDL_GetTicks() + 10000;
			QuestIndex = draw_quest(-1);
			if (QuestIndex < 0)
			{
				QuestIndex = RestartQuest;
				if (!SlayActive)
					start_slay();
			}
		}
		else
		{
			// Modes are drawn at random from those not completed; once all are done Peg Leg's loot follows
			QuestDone[QuestIndex] = true;
			QuestIndex = draw_quest(-1);
			if (QuestIndex < 0)
			{
				start_loot();
				QuestIndex = 0;
				say(pinball::MissTextBox, "Hit X to find Peg Leg's Loot", -1.0f, 1);
			}
		}
		if (pb::MainTable->ScoreMultiplier < 4)
			++pb::MainTable->ScoreMultiplier;
		show_quest();
	}

	void begin_quest(bool restart)
	{
		if (restart)
		{
			QuestIndex = RestartQuest;
			RestartEnd = 0;
		}
		StartHits = 0;
		QuestActive = true;
		QuestHits = 0;
		HoardMask = 0;
		BermudaCount = 0;
		ModeStart = SDL_GetTicks();
		TreasureX = rand() % 5;
		BuriedCoins = BuriedSpecial = BuriedBonus = BuriedJackpot = 0;
		BuriedExtra = false;
		ParrotMask = VolcanoMask = 0;
		if (Rules == &Pirates && QuestIndex == 4)
		{
			// The storm level comes from the wind lights: squall, tropical storm, monsoon or hurricane. The lights are
			// approximated from the wind lane passes.
			int level = WindHits * 16 / 12;
			StormValue = level <= 5 ? 10000 : level <= 10 ? 25000 : level <= 15 ? 50000 : 100000;
			StormEvery = level <= 5 ? 8 : level <= 10 ? 7 : level <= 15 ? 6 : 5;
		}
		ModeEnd = SDL_GetTicks() + (unsigned)(1000 * (Rules == &Dragon ? DragonSeconds : PirateSeconds)[QuestIndex]);
		if (Rules == &Dragon && QuestIndex == 0)
		{
			// Dragon Hoard (original 0x428a80)
			diverter(1, 2);
			diverter(2, 2);
		}
		else if (Rules == &Dragon && QuestIndex == 2)
		{
			// Rescue Maiden (original 0x429510)
			diverter(0, 1);
			diverter(1, 2);
			diverter(2, 1);
			diverter(3, 1);
		}
		// the mode's start payout (the 0x4f handler of each mode; Dragon's Keep uses the profile's)
		pb::MainTable->AddScore(Rules->quests[QuestIndex].startPoints ? Rules->quests[QuestIndex].startPoints : Rules->startPoints);
		snprintf(Line, sizeof Line, "%s started", Rules->questWord);
		say(pinball::InfoTextBox, Line, 3.0f, 2);
	}

	// Dragon eggs: the lights count up to eight; the award pays the number of eggs held times 100,000 (FUN_004232b0)
	void egg_award(int count)
	{
		Eggs = Eggs + count > 8 ? 8 : Eggs + count;
		pb::MainTable->AddScore(Eggs * 100000);
		snprintf(Line, sizeof Line, "Dragon Eggs %d", Eggs);
		say(pinball::InfoTextBox, Line, 2.0f, 2);
	}

	// The dragon egg kickout offers a purchase for the eggs held. The highest affordable item is offered; the left flipper
	// buys it, the right flipper declines for 25,000. Costs: quest 1 egg, spell 4, weapon 5, armor 6, extra ball light 7,
	// extra ball 8. An item that is already maxed falls back to the next cheaper one.
	void open_egg_menu()
	{
		if (Eggs == 0)
		{
			pb::MainTable->AddScore(25000);
			say(pinball::InfoTextBox, "No Dragon Eggs", 2.0f, 2);
			return;
		}
		int tier = Eggs > 8 ? 8 : Eggs;
		if (tier >= 8 && !ExtraBallLight)
			tier = 7;
		if (tier == 7 && ExtraBallLight)
			tier = 6;
		if (tier == 6 && Armor >= 3)
			tier = 5;
		if (tier == 5 && Weapons >= 4)
			tier = 4;
		if (tier < 4)
			tier = 1;
		MenuTier = tier;
		MenuOpen = true;
		MenuEnd = SDL_GetTicks() + 10000;
		static const char* const texts[] = {"", "Start the next quest?", "", "", "Purchase Spell?", "Purchase Weapon?", "Purchase Armor?",
			"Purchase Extra Ball Light?", "Purchase Extra Ball?"};
		snprintf(Line, sizeof Line, "%s Yes [Left] No [Right]", texts[tier]);
		say(pinball::InfoTextBox, Line, 10.0f, 2);
	}

	void answer_egg_menu(bool yes)
	{
		MenuOpen = false;
		if (!yes)
		{
			pb::MainTable->AddScore(25000);
			return;
		}
		static const int cost[] = {0, 1, 0, 0, 4, 5, 6, 7, 8};
		Eggs -= cost[MenuTier];
		switch (MenuTier)
		{
		case 1:
			if (!QuestActive && QuestIndex >= 0 && !SlayActive)
				begin_quest(false);
			break;
		case 4: cast_spell(); break;
		case 5:
			++Weapons;
			pb::MainTable->AddScore(25000 + 10000 * (Weapons - 1));
			say(pinball::InfoTextBox, "Weapon", 2.0f, 2);
			break;
		case 6:
			++Armor;
			say(pinball::InfoTextBox, "Armor", 2.0f, 2);
			break;
		case 7:
			ExtraBallLight = true;
			say(pinball::InfoTextBox, "Extra Ball Light", 2.0f, 2);
			break;
		default: award(EXTRA_BALL); break;
		}
	}

	// Dragon Hoard: every gem is worth its own amount, all nine give the extra ball
	void hoard_gem(const char* name)
	{
		struct Gem { const char* name; int bit, value; const char* text; };
		static const Gem gems[] = {
			{"a_spot4", 2, 50000, "Diamond"}, {"a_spot5", 2, 50000, "Diamond"}, {"a_spot6", 2, 50000, "Diamond"},
			{"a_spot7", 2, 50000, "Diamond"}, {"a_spot22", 2, 50000, "Diamond"},
			{"a_spot1", 4, 60000, "Pearl"}, {"a_spot2", 4, 60000, "Pearl"}, {"a_spot3", 4, 60000, "Pearl"},
			{"a_spot8", 0x10, 70000, "Sapphire"}, {"a_spot10", 0x10, 70000, "Sapphire"},
			{"a_spot12", 0x10, 70000, "Sapphire"}, {"a_spot14", 0x10, 70000, "Sapphire"},
			{"a_sink1", 0x20, 100000, "Ruby"}, {"a_sink2", 0x20, 100000, "Ruby"},
			{"a_accl1", 0x100, 100000, "Opal"}, {"a_ramp103", 0x80, 250000, "Amethyst"}, {"a_ramp6", 8, 200000, "Emerald"},
			{"s_oneway5", 0x40, JACKPOT, "Jackpot"},
		};
		int bit = 0, value = 0;
		const char* text = nullptr;
		if (!strncmp(name, "a_bump", 6))
		{
			bit = 1;
			value = 10000;
			text = "Gold";
		}
		for (const Gem& g : gems)
			if (!strcmp(g.name, name))
			{
				bit = g.bit;
				value = g.value;
				text = g.text;
			}
		if (!bit)
			return;
		award(value);
		if (text)
			say(pinball::InfoTextBox, text, 2.0f, 2);
		HoardMask |= bit;
		if (HoardMask == 0x1ff)
		{
			HoardMask = 0;
			award(EXTRA_BALL);
		}
	}

	void hit(const char* name)
	{
		int index = -1;
		for (int i = 0; i < Rules->scoreCount; ++i)
			if (!strcmp(Rules->scores[i].name, name))
				index = i;
		// Components without a score of their own (sinks, kickouts, ramps, return exits) still take part in the quests
		// Bermuda Triangle: the wind lanes pay only their mode award (the state 5 branch of 0x4298f0 returns before the ladder)
		bool bermudaLane = Rules == &Pirates && QuestActive && QuestIndex == 3 && match(WindLanes, name);
		if (index >= 0 && !bermudaLane)
			pb::MainTable->AddScore(component_score(index));
		apply_lights(name);
		play_sounds(name);
		// Island lanes (original 0x429fa0, 0x42a060, 0x42a120): each lane lights its top light, then its bottom light; all six
		// lit raise the fathom level and the lights start again
		if (Rules == &Pirates)
		{
			static const char* const island[] = {"a_roll12", "a_roll11", "a_roll10"};
			for (int i = 0; i < 3; ++i)
				if (!strcmp(name, island[i]))
				{
					IslandMask |= IslandMask & 1 << i ? 8 << i : 1 << i;
					if (IslandMask == 63)
					{
						IslandMask = 0;
						fathom_up();
					}
				}
		}
		if (Rules == &Pirates && pirate_idle())
		{
			// Lane lights (original 0x429630, 0x429790, 0x429840, 0x4298f0, 0x4296d0 and the check at 0x424290): in the idle state
			// each of five lanes lights its light; when all five are lit the lights start again and 0x423aa0 lights a map piece
			// and pays One Million
			static const char* const lanes[] = {"s_trip11", "a_roll5", "a_roll1", "a_roll2", "a_roll3"};
			for (int i = 0; i < 5; ++i)
				if (!strcmp(name, lanes[i]) && (LaneMask |= 1 << i) == 31)
				{
					LaneMask = 0;
					map_piece();
				}
		}
		if (Rules == &Pirates && ShipMystery && !strcmp(name, "a_roll3"))
			shipwreck_mystery(); // original 0x4296d0
		if (Rules == &Dragon && !strncmp(name, "a_bump", 6) && ++ForestHits == 10)
		{
			ForestHits = 0;
			if (Weapons < 4)
			{
				// Every tenth forest bumper hit of a ball awards the next weapon (25,000 more each time, original 0x424bc0 and 0x423330)
				static const char* const weapons[] = {"Frantz's Ax", "Firebow", "Sword of Virtue", "Dragon Lance"};
				pb::MainTable->AddScore(25000 + 10000 * Weapons);
				snprintf(Line, sizeof Line, "%s", weapons[Weapons++]);
				say(pinball::InfoTextBox, Line, 3.0f, 2);
			}
		}
		if (match(Rules->targets, name))
		{
			Jackpot += Rules->jackpotTarget;
			++TargetsHit;
		}
		else if (match(Rules->sinks, name))
			Jackpot += Rules->jackpotSink;

		if (Rules == &Dragon)
		{
			// Skill shot (state 10 of the original): the first spell target the launched ball hits gives a spell (a_spot4), a dragon
			// egg (a_spot5), a weapon (a_spot6), armor (a_spot7) or Gargoyle Gaggle-Ball (a_spot22)
			if (FirstHit)
			{
				FirstHit = false;
				static const char* const skill[] = {"a_spot4", "a_spot5", "a_spot6", "a_spot7", "a_spot22"};
				for (int i = 0; i < 5; ++i)
					if (!strcmp(name, skill[i]))
					{
						if (i == 1) egg_award(1);
						else if (i == 2 && Weapons < 4) pb::MainTable->AddScore(25000 + 10000 * Weapons++);
						else if (i == 3 && Armor < 3) ++Armor;
						else if (i == 4 && !MultiMode) start_multiball(MULTI_GAGGLE, 1, "Gargoyle Gaggle-Ball");
						else if (i == 0) cast_spell();
						static const char* const said[] = {"Skill Shot: Spell", "Skill Shot: Dragon Egg", "Skill Shot: Weapon", "Skill Shot: Armor", "Skill Shot: Gaggle-Ball"};
						say(pinball::InfoTextBox, said[i], 3.0f, 2);
					}
			}
			// All five spell targets hit cast a spell
			for (int i = 0; i < 5; ++i)
				if (!strcmp(name, SpellTargets[i]))
				{
					SpellMask |= 1 << i;
					if (SpellMask == 31)
					{
						SpellMask = 0;
						dragon_letter(1);
						cast_spell();
					}
				}
			// The dragon egg kickout (a_kout2) offers a purchase for the eggs held; during Dragon Pass it awards an egg.
			// The return exits give two eggs and the dragon ramp loop adds to the jackpot.
			// The gargoyle kickout (a_kout2) starts Gargoyle Gaggle-Ball, during Dragon Pass it awards an egg; the dragon egg
			// hole (s_hole118) opens the egg purchase
			if (!strcmp(name, "a_kout2"))
			{
				if (QuestActive && QuestIndex == 3)
					egg_award(1);
				else if (!QuestActive && !SlayActive && !MultiMode)
					start_multiball(MULTI_GAGGLE, 1, "Gargoyle Gaggle-Ball");
			}
			if (!strcmp(name, "a_sink4") && !QuestActive && !SlayActive && !MultiMode)
			{
				// original 0x426140 in the idle state: a quarter of the balls in the well start the drawn quest, the rest
				// cast a spell
				if (rand() % 4 != 1)
					cast_spell();
				else if (QuestIndex >= 0)
				{
					begin_quest(false);
					return; // the ball that starts the quest does not count as its first hit
				}
			}
			if (!strcmp(name, "s_hole118") && !QuestActive && !SlayActive)
				open_egg_menu();
			// Dragon letters: both fire lizard sinks, the spell bank, the dragon loop, the gargoyle bank, the tower ramp and the
			// tower bank (which also lights the tower lock)
			if (!strcmp(name, "a_sink1") || !strcmp(name, "a_sink2"))
				if ((FireMask |= name[6] == '1' ? 1 : 2) == 3)
				{
					FireMask = 0;
					dragon_letter(0);
				}
			if (!strcmp(name, "a_ramp103"))
				dragon_letter(2);
			if (!strcmp(name, "a_ramp6"))
				dragon_letter(4);
			{
				static const char* const gargoyle[] = {"a_spot8", "a_spot10", "a_spot12", "a_spot14"};
				for (int i = 0; i < 4; ++i)
					if (!strcmp(name, gargoyle[i]) && (GargoyleMask |= 1 << i) == 15)
					{
						GargoyleMask = 0;
						diverter(1, 1);
						diverter(2, 1);
						dragon_letter(3);
					}
				static const char* const tower[] = {"a_spot1", "a_spot2", "a_spot3"};
				for (int i = 0; i < 3; ++i)
					if (!strcmp(name, tower[i]) && (TowerMask |= 1 << i) == 7)
					{
						TowerMask = 0;
						// original 0x4250e0: in the idle state the gates move only when the sixth letter does not complete the six
						// (0x4244e0 starts Dragon Flurry instead, and the gates stay)
						if (!QuestActive && !SlayActive && !MultiMode && (LetterMask | 1 << 5) != 63)
						{
							diverter(0, 1);
							diverter(3, 1);
						}
						dragon_letter(5);
						if (!LockLit && !MultiMode && !QuestActive && !SlayActive)
						{
							LockLit = true;
							say(pinball::InfoTextBox, "Tower Lock Enabled", 2.0f, 2);
						}
					}
			}
			if (!strcmp(name, "s_rexit18") || !strcmp(name, "s_rexit19"))
				egg_award(2);
			// Diverter positions of the lane and sink handlers (original 0x426a50, 0x4274d0, 0x427680, 0x4267f0, 0x4265e0, 0x426c20, 0x426be0)
			{
				bool idle = !QuestActive && !SlayActive && !MultiMode;
				if (!strcmp(name, "a_roll7"))
					diverter(0, 1);
				else if ((!strcmp(name, "a_sink9") || !strcmp(name, "a_sink10")) && !tower_busy())
				{
					diverter(0, 2);
					diverter(3, 2);
				}
				else if (!strcmp(name, "s_oneway5") && idle)
					diverter(3, 1);
				else if (!strcmp(name, "a_ramp103") && !tower_busy())
					diverter(3, 2);
				else if (!strcmp(name, "s_rexit18") && idle)
					diverter(1, 2);
				else if (!strcmp(name, "s_rexit19") && idle)
					diverter(2, 2);
			}
			if (!strcmp(name, "a_ramp103") && !(QuestActive && QuestIndex == 0))
			{
				LoopCount = SDL_GetTicks() - LoopTime > 10000 ? 0 : (LoopCount < 9 ? LoopCount + 1 : 9);
				LoopTime = SDL_GetTicks();
				int add = (LoopCount + 1) * 50000;
				pb::MainTable->AddScore(add);
				Jackpot += add;
				snprintf(Line, sizeof Line, "Dragon Loop %d Added to Jackpot", add);
				say(pinball::InfoTextBox, Line, 2.0f, 2);
			}
			dragon_slay(name);
			// The spell targets set the mystery award of Wizard's Fury
			for (int i = 0; i < 5; ++i)
				if (!strcmp(name, SpellTargets[i]) && QuestActive && QuestIndex == 4 && MysteryIdx != i)
				{
					Mystery = SpellAwards[i];
					MysteryIdx = i;
					static const char* const names[] = {"Extra Ball", "Max Weapons", "Max Armor", "Jackpot", "One Million"};
					snprintf(Line, sizeof Line, "Mystery Bonus set to: %s", names[i]);
					say(pinball::InfoTextBox, Line, 3.0f, 2);
				}
		}

		if (Rules == &Pirates && QuestActive && !strcmp(name, Rules->selectTarget))
		{
			ModeEnd += 10000;
			say(pinball::InfoTextBox, "Time Extended", 2.0f, 2);
		}

		// The quest selection target draws another of the quests not completed yet
		if (!strcmp(name, Rules->selectTarget) && !QuestActive && !SlayActive)
		{
			if (Rules == &Dragon && ExtraBallLight)
			{
				ExtraBallLight = false;
				award(EXTRA_BALL);
			}
			int next = draw_quest(QuestIndex);
			if (next >= 0)
			{
				QuestIndex = next;
				static const char* const dragonPicks[] = {"Dragon Hoard", "Fire Lizards", "Rescue Maiden", "Dragon Pass", "Wizard's Fury"};
				static const char* const piratePicks[] = {"Attack", "Treasure Hunt", "Tavern", "Bermuda", "Storm", "Mutiny", "Swordfight"};
				const char* const* picks = Rules == &Dragon ? dragonPicks : piratePicks;
				snprintf(Line, sizeof Line, Rules == &Dragon ? "%s Quest Selected" : "%s Mode Selected", picks[next]);
				say(pinball::InfoTextBox, Line, 2.0f, 2);
			}
		}

		if (Rules == &Pirates && match(WindLanes, name) && WindHits < 12)
			++WindHits;

		if (QuestActive && SDL_GetTicks() > ModeEnd)
			end_quest();

		if (LootActive)
		{
			// Peg Leg's Loot (state 0xb of the original): the hideaways award special treasures, the ship sink finds the loot
			if (match(Hideaways, name))
			{
				special_treasure();
			}
			else if (!strcmp(name, "a_sink4"))
			{
				int loot = QuestsDone * 1000000 + Treasures * 500000 + Coins * 500000 + MapPieces * 1000000;
				pb::MainTable->AddScore(loot);
				fathom_up(); // original 0x42cfc0
				snprintf(Line, sizeof Line, "Peg Leg's Loot %d", loot);
				say(pinball::InfoTextBox, Line, 5.0f, 2);
				LootActive = false;
				MapPieces = 0;
				memset(QuestDone, 0, sizeof QuestDone);
				QuestIndex = draw_quest(-1);
				pb::MainTable->ScoreMultiplier = 4;
				show_quest();
			}
			return;
		}

		// The brig (original 0x429040 and the jail routine 0x424210): a trapped ball is sent back out through the launcher;
		// the third trap is held instead, which starts Jail Break (0x42d590): it pays 100,000 and releases the held balls
		if (Rules == &Pirates && !strcmp(name, "s_hole19"))
		{
			// The hole gives the ball back itself, so the first two traps change nothing; the held ball is one of the three
			if (++HeldBalls == 3)
			{
				HeldBalls = 0;
				pb::MainTable->AddScore(100000);
				say(pinball::InfoTextBox, "Jail Break!", 3.0f, 2);
				feed_balls(2);
			}
		}

		// Lava-Ball (original 0x427540, idle state): with all four volcano lights lit, two balls are queued for the plunger
		if (Rules == &Pirates && !QuestActive)
		{
			static const char* const lava[] = {"a_spot8", "a_spot9", "a_spot10", "a_spot11"};
			for (int i = 0; i < 4; ++i)
				if (!strcmp(name, lava[i]))
					LavaMask |= 1 << i;
			if (LavaMask == 15)
			{
				LavaMask = 0;
				say(pinball::InfoTextBox, "Lava-Ball", 3.0f, 2);
				feed_balls(2);
			}
		}

		if (!QuestActive && Rules == &Pirates)
		{
			// SKULDUGGERY: one light per letter, lit by eleven drop targets (original 0x4268b0 and the others, which set
			// bits 0x1 to 0x400 of v_lite1). When all eleven are lit the mode is chosen (original 0x425de0)
			// Jail Break from the idle state (original 0x4279b0 and 0x42d590): the third hit of a_spot6 pays the held balls
			// (100,000) and releases them; with none held it does nothing
			if (!strcmp(name, "a_spot6") && ++Spot6Hits == 3)
			{
				Spot6Hits = 0;
				if (HeldBalls)
				{
					// the brig hole gave those balls back itself (see s_hole19), so no ball is fed here
					pb::MainTable->AddScore(100000);
					say(pinball::InfoTextBox, "Jail Break!", 3.0f, 2);
					HeldBalls = 0;
				}
			}
			static const char* const letters[] = {"a_drop5", "a_drop6", "a_drop7", "a_drop8", "a_drop9", "a_drop10", "a_drop11", "a_drop12", "a_drop13", "a_drop14", "a_drop15"};
			for (int i = 0; i < 11; ++i)
				if (!strcmp(name, letters[i]))
					PirateLetters |= 1 << i;
			if (PirateLetters == 0x7ff)
			{
				PirateLetters = 0;
				begin_quest(false);
			}
			show_quest();
			return;
		}
		if (!QuestActive)
		{
			bool restart = Rules == &Dragon && RestartEnd && SDL_GetTicks() < RestartEnd && match(Rules->startRoles, name);
			if (restart || (match(Rules->startRoles, name) && ++StartHits >= Rules->startHits))
			{
				begin_quest(restart);
			}
			show_quest();
			return;
		}

		// In Tavern mode the window sinks give the random award
		if (Rules == &Pirates && QuestIndex == 2 && (!strcmp(name, "a_sink5") || !strcmp(name, "a_sink6") || !strcmp(name, "a_sink7")))
			random_award();

		if (Rules == &Pirates && QuestIndex == 6)
		{
			// Swordfight: finishing the parrot bank or the volcano bank gives a coin award, special treasure, map piece or extra ball
			static const char* const parrot[] = {"a_drop10", "a_drop11", "a_drop12"};
			static const char* const volcano[] = {"a_spot8", "a_spot9", "a_spot10", "a_spot11"};
			bool full = false;
			for (int i = 0; i < 3; ++i)
				if (!strcmp(name, parrot[i]))
					full = (ParrotMask |= 1 << i) == 7 && ((ParrotMask = 0), true);
			for (int i = 0; i < 4; ++i)
				if (!strcmp(name, volcano[i]))
					full = (VolcanoMask |= 1 << i) == 15 && ((VolcanoMask = 0), true);
			if (full)
			{
				random_award();
				if (MapPieces >= 6 && !LootActive)
				{
					start_loot();
					show_quest();
				}
			}
		}

		const Quest& q = Rules->quests[QuestIndex];
		if (Rules == &Dragon && QuestIndex == 0)
		{
			hoard_gem(name);
			return;
		}
		if (Rules == &Dragon && QuestIndex == 3)
		{
			// Dragon Pass: gargoyle targets give 100,000 and add 250,000 to the jackpot, the armor kickout awards the jackpot
			// (the egg of the other kickout is counted with the dragon eggs above)
			if (!strcmp(name, "a_spot8") || !strcmp(name, "a_spot10") || !strcmp(name, "a_spot12") || !strcmp(name, "a_spot14"))
			{
				pb::MainTable->AddScore(100000);
				Jackpot += 250000;
			}
			else if (!strcmp(name, "a_kout1"))
				award(JACKPOT);
			return;
		}
		if (Rules == &Pirates && QuestIndex == 4 && (!strcmp(name, "a_sink17") || !strcmp(name, "a_sink15") || !strcmp(name, "a_sink14")))
		{
			// original 0x42c430: a ball in a hideaway wrecks the ship and ends the storm with the mystery available
			say(pinball::InfoTextBox, "Shipwrecked", 2.0f, 2);
			ShipMystery = true;
			end_quest();
			say(pinball::InfoTextBox, "Shipwreck Mystery\nAvailable", 3.0f, 2);
			return;
		}
		if (Rules == &Pirates && QuestIndex == 0 && !strcmp(name, "s_trip2"))
		{
			// original 0x4290c0 and 0x424440: during Attack Ship the sensor s_trip2 raises the ship targets again
			for (int i = 0; ShipTargets[i]; ++i)
				if (auto drop = pb::MainTable->find_component(ShipTargets[i]))
					drop->Message(50, 0.0f);
			return;
		}
		if (Rules == &Pirates && QuestIndex == 0 && !strcmp(name, "s_rexit8"))
		{
			// original 0x429140: during Attack Ship the wire ramp captures the ship: the ship targets come back up and the
			// fathom level goes up
			say(pinball::InfoTextBox, "Ship Captured", 2.0f, 2);
			for (int i = 0; ShipTargets[i]; ++i)
				if (auto drop = pb::MainTable->find_component(ShipTargets[i]))
					drop->Message(50, 0.0f);
			fathom_up();
			return;
		}
		if (!match(q.roles, name))
			return;
		if (Rules == &Pirates && QuestIndex == 1)
		{
			// Treasure Hunt: only the hideaway with the flashing X counts; the X then moves to another hideaway
			if (strcmp(name, Hideaways[TreasureX]))
				return;
			int next = rand() % 4;
			TreasureX = next >= TreasureX ? next + 1 : next;
			// original 0x424b00: the finds are buried and paid when the mode ends: three coin awards, two special
			// treasures, a bonus, the jackpot and an extra ball, then coin awards again
			static const char* const buried[] = {"Coins\nBuried", "Coins\nBuried", "Coins\nBuried", "Special Treasure\nBuried",
				"Special Treasure\nBuried", "Bonus\nBuried", "Jackpot\nBuried", "Extra Ball\nBuried"};
			int find = QuestHits < 8 ? QuestHits : 0;
			say(pinball::InfoTextBox, buried[find], 3.0f, 2);
			if (find < 3) ++BuriedCoins;
			else if (find < 5) ++BuriedSpecial;
			else if (find == 5) BuriedBonus = ((Treasures * 2 + MapPieces) * 25 + QuestsDone * 20 + TargetsHit) * Fathom * 10000; // original 0x424aa0
			else if (find == 6) BuriedJackpot = Jackpot;
			else BuriedExtra = true;
			++QuestHits;
			Jackpot += q.jackpotAdd;
			if (QuestHits < q.goal)
			{
				show_quest();
				return;
			}
			end_quest();
			return;
		}
		if (Rules == &Pirates && QuestIndex == 0)
		{
			// original 0x4264f0 (state 4): a ship target pays 10,000; all five sink the ship: the jackpot and 25,000, the targets
			// come back up and the mode goes on until its timer ends
			if (++QuestHits % 5)
				pb::MainTable->AddScore(10000);
			else
			{
				award(JACKPOT);
				pb::MainTable->AddScore(25000);
				say(pinball::InfoTextBox, "Ship Sunk", 2.0f, 2);
				for (int i = 0; ShipTargets[i]; ++i)
					if (auto drop = pb::MainTable->find_component(ShipTargets[i]))
						drop->Message(50, 0.0f);
			}
			return;
		}
		if (Rules == &Pirates && QuestIndex == 3)
		{
			// Bermuda Triangle: the indicated wind lane pays 125,000 / 250,000 / 500,000 / 1,000,000 / jackpot, the others 50,000.
			// The indicator moves on every 0.1 seconds (the light group timer of the original, handler 0x47).
			if (strcmp(name, WindLanes[((SDL_GetTicks() - ModeStart) / 100) % 4]))
				pb::MainTable->AddScore(50000);
			else
			{
				static const int pay[] = {125000, 250000, 500000, 1000000};
				if (BermudaCount < 4)
					pb::MainTable->AddScore(pay[BermudaCount++]);
				else
				{
					BermudaCount = 0;
					award(JACKPOT);
				}
			}
			++QuestHits;
			return;
		}
		int n = QuestHits++;
		Jackpot += q.jackpotAdd;
		if (Rules == &Pirates && QuestIndex == 4)
		{
			pb::MainTable->AddScore(StormValue);
			if (QuestHits % StormEvery == 0)
				award(JACKPOT);
		}
		else if (Rules == &Dragon && QuestIndex == 2)
		{
			// Rescue Maiden: the prison windows count 250,000, 500,000, jackpot, extra ball light, then start over
			switch (n % 4)
			{
			case 0: pb::MainTable->AddScore(250000); break;
			case 1: pb::MainTable->AddScore(500000); break;
			case 2: award(JACKPOT); break;
			default:
				ExtraBallLight = true;
				say(pinball::InfoTextBox, "Maiden Rescued Extra Ball Available", 3.0f, 2);
			}
		}
		else if (Rules == &Dragon && QuestIndex == 1)
		{
			// Fire Lizards: each hit is worth 100,000 more, up to a million, and every fourth hit awards the jackpot
			if (QuestHits % 4 == 0)
				award(JACKPOT);
			else
				pb::MainTable->AddScore((QuestHits < 10 ? QuestHits : 10) * 100000);
		}
		else
			award(q.awards[n < 5 ? n : 5]);
		if (Rules == &Pirates && QuestIndex == 4)
			;
		else if (q.jackpotEvery && QuestHits % q.jackpotEvery == 0)
			award(JACKPOT);
		if (QuestHits < q.goal)
		{
			show_quest();
			return;
		}

		end_quest();
	}

	// Ball lost: shoot again if it drains in the first 15 seconds, else the bonus, next ball or game over
	void drain(int code)
	{
		TPinballTable* table = pb::MainTable;
		if (code == 60)
		{
			if (LastBallLost)
			{
				table->Message(1022, 0.0f);
				pb::chk_highscore();
			}
			else if (table->Plunger)
				table->Plunger->Message(1016, 0.0f);
			return;
		}
		if (LaunchTicks && SDL_GetTicks() - LaunchTicks < 15000 && !table->TiltLockFlag)
		{
			say(pinball::InfoTextBox, "Shoot Again", 3.0f, 2);
			LaunchTicks = 0;
			return;
		}
		LaunchTicks = 0;
		if (QuestActive)
			end_quest();
		Fathom = 1; // the launcher of the original (0x425e70) clears the fathom lights for each ball
		LavaMask = LaneMask = 0; // the volcano and lane lights start again on each ball
		ForestHits = SwordHits = 0;
		if (!table->TiltLockFlag)
		{
			int bonus = TargetsHit * Rules->bonusPerTarget + QuestsDone * Rules->bonusPerQuest + (Rules == &Dragon ? Armor * 50000 + Spells * 75000 + Eggs * 150000 + (Weapons ? (Weapons + 1) * 75000 : 0) : MapPieces * 250000 + Treasures * 100000);
			if (Rules == &Dragon)
			{
				// original 0x42b7c0: the held bonus is added, and the total is held for the next ball when the hold light is on
				bonus += BonusHold;
				BonusHold = BonusHoldLit ? bonus : 0;
				BonusHoldLit = false;
			}
			if (bonus > 0)
			{
				snprintf(Line, sizeof Line, "Total Bonus %d", bonus);
				table->AddScore(bonus);
				say(pinball::InfoTextBox, Line, 3.0f, 2);
			}
		}
		TargetsHit = 0;
		Eggs = 0;
		RestartEnd = 0;
		memset(Hits, 0, sizeof Hits);
		memset(RouteCombo, 0, sizeof RouteCombo);
		memset(RouteLights, 0, sizeof RouteLights);
		LastRoute = -1;
		memset(BankPaid, 0, sizeof BankPaid);
		table->ScoreMultiplier = 0;
		end_multiball_state();
		BallsInPlay = 1;
		MultiMode = MULTI_NONE;
		reset_diverters(); // after the multiball state, so that the tower gates are not skipped
		if (table->ExtraBalls)
		{
			--table->ExtraBalls;
			say(pinball::InfoTextBox, "Shoot Again", -1.0f, 2);
			return;
		}
		table->ChangeBallCount(table->BallCount - 1);
		if (table->CurrentPlayer + 1 != table->PlayerCount || table->BallCount)
		{
			table->Message(1021, 0.0f);
			LastBallLost = false;
		}
		else
			LastBallLost = true;
	}

	void lenient_rules(int code, TPinballComponent* cmp)
	{
		if (!pb::MainTable)
			return;
		if (dynamic_cast<TDrain*>(cmp))
		{
			if (code == 2000)
			{
				extra_ball_lost();
				return;
			}
			if (code == 60 || code == 63)
				drain(code);
			return;
		}
		if (code == 1 && MenuOpen && cmp->GroupName && !strncmp(cmp->GroupName, "a_flip", 6))
		{
			if (SDL_GetTicks() > MenuEnd)
				MenuOpen = false;
			else
				answer_egg_menu(!strcmp(cmp->GroupName, "a_flip1"));
			return;
		}
		if (code == 1005 && dynamic_cast<TPlunger*>(cmp))
		{
			LaunchTicks = SDL_GetTicks();
			FirstHit = true;
			return;
		}
		if ((code != 63 && code != 57) || !cmp->GroupName)
			return;
		if (pb::MainTable->CurScore == 0 && pb::MainTable->CurScoreE9 == 0)
			new_game();
		hit(cmp->GroupName);
		// The sinks of the other tables kick the ball out again after their own time, unless it stays locked
		if (code == 63 && dynamic_cast<TSink*>(cmp) && !lock_ball(cmp))
			cmp->Message(56, -1.0f);
	}
}

void control::handler(int code, TPinballComponent* cmp)
{
	// The table rules in this file are Space Cadet's: other Full Tilt tables run without rules
	if (loader::Lenient)
	{
		lenient_rules(code, cmp);
		return;
	}
	component_control* control = cmp->Control;
	
	if (control)
	{
		if (code == 1019)
		{
			for (auto scoreInd = 0; scoreInd < control->ScoreCount; ++scoreInd)
			{
				cmp->put_scoring(scoreInd, control->Scores[scoreInd]);
			}
		}
		control->ControlFunc(code, cmp);
	}
	MissionControl(code, cmp);
}

void control::pbctrl_bdoor_controller(char key)
{
	// Buffer large enough for longest cheat + null
	static char cheatBuffer[11 + 1]{};
	static char* bufferEnd = &cheatBuffer[11];
	static const char* quotes[8]
	{
		"Hey, is that a screen saver?",
		"I guess it has been a good week",
		"She may already be a glue bottle",
		"If you don't come in Saturday,\n...\n",
		"don't even bother coming in Sunday.",
		"Tomorrow already sucks",
		"I knew it worked too good to be right.",
		"World's most expensive flippers"
	};

	// Original allowed to enter cheats only before the first launch.
	std::memmove(&cheatBuffer[0], &cheatBuffer[1], 10);
	cheatBuffer[10] = key;

	if (strcmp(bufferEnd - 11, "hidden test") == 0)
	{
		pb::cheat_mode ^= true;
	}
	else if (strcmp(bufferEnd - 4, "gmax") == 0)
	{
		GravityWellKickoutControl(64, nullptr);
	}
	else if (strcmp(bufferEnd - 4, "1max") == 0)
	{
		table_add_extra_ball(2.0);
	}
	else if (strcmp(bufferEnd - 4, "bmax") == 0)
	{
		table_unlimited_balls ^= true;
	}
	else if (strcmp(bufferEnd - 4, "rmax") == 0)
	{
		cheat_bump_rank();
	}
	else if (pb::FullTiltMode && strcmp(bufferEnd - 5, "quote") == 0)
	{
		// A sad developer easter egg type 'cheat' from Full Tilt 
		float time = 0;
		for (auto quote : quotes)
			control_mission_text_box_tag.Component->Display(quote, time += 3, 1);
		return;
	}
	else
	{
		return;
	}

	TableG->CheatsUsed = 1;
    SpaceCadetPinballJNI::cheatsUsed();
}

bool control::check_cheats()
{
    if (TableG == nullptr) return false;
    else return TableG->CheatsUsed == 1;
}

void control::table_add_extra_ball(float count)
{
	++TableG->ExtraBalls;
	control_soundwave28_tag.Component->Play();
	auto msg = pinball::get_rc_string(9, 0);
	control_info_text_box_tag.Component->Display(msg, count, 2);
}

void control::table_set_bonus_hold()
{
	control_lite58_tag.Component->Message(19, 0.0);
	control_info_text_box_tag.Component->Display(pinball::get_rc_string(52, 0), 2.0, 2);
}

void control::table_set_bonus()
{
	TableG->ScoreSpecial2Flag = 1;
	control_lite59_tag.Component->Message(9, 60.0);
	control_info_text_box_tag.Component->Display(pinball::get_rc_string(4, 0), 2.0, 2);
}

void control::table_set_jackpot()
{
	TableG->ScoreSpecial3Flag = 1;
	control_lite60_tag.Component->Message(9, 60.0);
	control_info_text_box_tag.Component->Display(pinball::get_rc_string(15, 0), 2.0, 2);
}

void control::table_set_flag_lights()
{
	control_lite20_tag.Component->Message(9, 60.0);
	control_lite19_tag.Component->Message(9, 60.0);
	control_lite61_tag.Component->Message(9, 60.0);
	control_info_text_box_tag.Component->Display(pinball::get_rc_string(51, 0), 2.0, 2);
}

void control::table_set_multiball()
{
	control_info_text_box_tag.Component->Display(pinball::get_rc_string(16, 0), 2.0, 2);
}

void control::table_bump_ball_sink_lock()
{
	if (TableG->BallLockedCounter == 2)
	{
		table_set_multiball();
		TableG->BallLockedCounter = 0;
	}
	else
	{
		TableG->BallLockedCounter = TableG->BallLockedCounter + 1;
		control_soundwave44_tag.Component->Play();
		control_info_text_box_tag.Component->Display(pinball::get_rc_string(1, 0), 2.0, 2);
		TableG->Plunger->Message(1016, 0.0);
	}
}

void control::table_set_replay(float value)
{
	control_lite199_tag.Component->Message(19, 0.0);
	control_info_text_box_tag.Component->Display(pinball::get_rc_string(0, 0), value, 2);
}

void control::cheat_bump_rank()
{
	char Buffer[64]{};

	auto rank = control_middle_circle_tag.Component->Message(37, 0.0);
	if (rank < 9)
	{
		control_middle_circle_tag.Component->Message(41, 2.0f);
		auto rankText = pinball::get_rc_string(RankRcArray[rank], 1);
		snprintf(Buffer,sizeof Buffer, pinball::get_rc_string(83, 0), rankText);
		control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
		control_soundwave10_tag.Component->Play();
	}
}

bool control::light_on(component_tag<TLight>* tag)
{
	auto light = tag->Component;
	return light->BmpIndex1 || light->FlasherFlag2 || light->FlasherActive;
}

int control::SpecialAddScore(int score)
{
	int prevFlag1 = TableG->ScoreSpecial3Flag;
	TableG->ScoreSpecial3Flag = 0;
	int prevFlag2 = TableG->ScoreSpecial2Flag;
	TableG->ScoreSpecial2Flag = 0;
	int prevMult = TableG->ScoreMultiplier;
	TableG->ScoreMultiplier = 0;

	int addedScore = TableG->AddScore(score);
	TableG->ScoreSpecial2Flag = prevFlag2;
	TableG->ScoreMultiplier = prevMult;
	TableG->ScoreSpecial3Flag = prevFlag1;
	return addedScore;
}

int control::AddRankProgress(int rank)
{
	char Buffer[64];
	int result = 0;

	control_lite16_tag.Component->Message(19, 0.0);
	TPinballComponent* outerCircle = control_outer_circle_tag.Component;
	for (int index = rank; index; --index)
	{
		outerCircle->Message(41, 2.0);
	}

	int activeCount = outerCircle->Message(37, 0.0);
	int totalCount = outerCircle->Message(38, 0.0);
	if (activeCount == totalCount)
	{
		result = 1;
		outerCircle->Message(16, 5.0);
		TPinballComponent* middleCircle = control_middle_circle_tag.Component;
		control_middle_circle_tag.Component->Message(34, 0.0);
		int midActiveCount = middleCircle->Message(37, 0.0);
		if (midActiveCount < 9)
		{
			middleCircle->Message(41, 5.0);
			auto rankText = pinball::get_rc_string(RankRcArray[midActiveCount], 1);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(83, 0), rankText);
			control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
			control_soundwave10_tag.Component->Play();
		}
	}
	else if (activeCount >= 3 * totalCount / 4)
	{
		control_middle_circle_tag.Component->Message(27, -1.0);
	}
	return result;
}

void control::AdvanceWormHoleDestination(int flag)
{
	int lite198Msg = control_lite198_tag.Component->MessageField;
	if (lite198Msg != 16 && lite198Msg != 22 && lite198Msg != 23)
	{
		int lite4Msg = control_lite4_tag.Component->MessageField;
		if (flag || lite4Msg)
		{
			int val1 = lite4Msg + 1;
			int val2 = val1;
			if (val1 == 4)
			{
				val1 = 1;
				val2 = 1;
			}
			control_bsink_arrow_lights_tag.Component->Message(23, static_cast<float>(val2));
			control_bsink_arrow_lights_tag.Component->Message(11, static_cast<float>(3 - val1));
			if (!light_on(&control_lite4_tag))
			{
				control_worm_hole_lights_tag.Component->Message(19, 0.0);
				control_bsink_arrow_lights_tag.Component->Message(19, 0.0);
			}
		}
	}
}

void control::FlipperRebounderControl1(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		control_lite84_tag.Component->Message(9, 0.1f);
		auto score = caller->get_scoring(0);
		TableG->AddScore(score);
	}
}

void control::FlipperRebounderControl2(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		control_lite85_tag.Component->Message(9, 0.1f);
		int score = caller->get_scoring(0);
		TableG->AddScore(score);
	}
}

void control::RebounderControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::BumperControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		TableG->AddScore(caller->get_scoring(static_cast<TBumper*>(caller)->BmpIndex));
	}
}

void control::LeftKickerControl(int code, TPinballComponent* caller)
{
	if (code == 60)
		control_gate1_tag.Component->Message(54, 0.0);
}

void control::RightKickerControl(int code, TPinballComponent* caller)
{
	if (code == 60)
		control_gate2_tag.Component->Message(54, 0.0);
}

void control::LeftKickerGateControl(int code, TPinballComponent* caller)
{
	if (code == 53)
	{
		control_lite30_tag.Component->Message(15, 5.0);
		control_lite196_tag.Component->Message(7, 5.0);
	}
	else if (code == 54)
	{
		control_lite30_tag.Component->Message(20, 0.0);
		control_lite196_tag.Component->Message(20, 0.0);
	}
}

void control::RightKickerGateControl(int code, TPinballComponent* caller)
{
	if (code == 53)
	{
		control_lite29_tag.Component->Message(15, 5.0);
		control_lite195_tag.Component->Message(7, 5.0);
	}
	else if (code == 54)
	{
		control_lite29_tag.Component->Message(20, 0.0);
		control_lite195_tag.Component->Message(20, 0.0);
	}
}

void control::DeploymentChuteToEscapeChuteOneWayControl(int code, TPinballComponent* caller)
{
	char Buffer[64];
	if (code == 63)
	{
		int count = control_skill_shot_lights_tag.Component->Message(37, 0.0);
		if (count)
		{
			control_soundwave3_tag.Component->Play();
			int score = TableG->AddScore(caller->get_scoring(count - 1));
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(21, 0), score);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			if (!light_on(&control_lite56_tag))
			{
				control_l_trek_lights_tag.Component->Message(34, 0.0);
				control_l_trek_lights_tag.Component->Message(20, 0.0);
				control_r_trek_lights_tag.Component->Message(34, 0.0);
				control_r_trek_lights_tag.Component->Message(20, 0.0);
			}
			control_skill_shot_lights_tag.Component->Message(44, 1.0);
		}
	}
}

void control::DeploymentChuteToTableOneWayControl(int code, TPinballComponent* caller)
{
	if (code == 63)
		control_skill_shot_lights_tag.Component->Message(20, 0.0);
}

void control::DrainBallBlockerControl(int code, TPinballComponent* caller)
{
	int msgCode;
	float msgValue;

	auto block = static_cast<TBlocker*>(caller);
	if (code == 52)
	{
		block->MessageField = 1;
		block->Message(52, static_cast<float>(block->TurnOnMsgValue));
		msgValue = static_cast<float>(block->TurnOnMsgValue);
		msgCode = 9;
	}
	else
	{
		if (code != 60)
			return;
		if (block->MessageField != 1)
		{
			block->MessageField = 0;
			block->Message(51, 0.0);
			return;
		}
		block->MessageField = 2;
		block->Message(59, static_cast<float>(block->TurnOffMsgValue));
		msgValue = static_cast<float>(block->TurnOffMsgValue);
		msgCode = 7;
	}
	control_lite1_tag.Component->Message(msgCode, msgValue);
}

void control::LaunchRampControl(int code, TPinballComponent* caller)
{
	TSound* sound;
	char Buffer[64];

	if (code == 63)
	{
		int someFlag = 0;
		if (light_on(&control_lite54_tag))
		{
			someFlag = 1;
			int addedScore = SpecialAddScore(TableG->ScoreSpecial1);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(10, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
		}
		if (light_on(&control_lite55_tag))
			someFlag |= 2u;
		if (light_on(&control_lite56_tag))
			someFlag |= 4u;
		if (someFlag)
		{
			if (someFlag == 1)
			{
				sound = control_soundwave21_tag.Component;
			}
			else if (someFlag < 1 || someFlag > 3)
			{
				sound = control_soundwave24_tag.Component;
			}
			else
			{
				sound = control_soundwave23_tag.Component;
			}
		}
		else
		{
			TableG->AddScore(caller->get_scoring(0));
			sound = control_soundwave30_tag.Component;
		}
		sound->Play();
	}
}

void control::LaunchRampHoleControl(int code, TPinballComponent* caller)
{
	if (code == 58)
		control_lite54_tag.Component->Message(7, 5.0);
}

void control::SpaceWarpRolloverControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		control_lite27_tag.Component->Message(19, 0.0);
		control_lite28_tag.Component->Message(19, 0.0);
	}
}

void control::ReentryLanesRolloverControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (!light_on(&control_lite56_tag) && control_l_trek_lights_tag.Component->Message(39, 0.0))
		{
			control_l_trek_lights_tag.Component->Message(34, 0.0);
			control_l_trek_lights_tag.Component->Message(20, 0.0);
			control_r_trek_lights_tag.Component->Message(34, 0.0);
			control_r_trek_lights_tag.Component->Message(20, 0.0);
		}

		TLight* light;
		if (control_roll3_tag.Component == caller)
		{
			light = control_lite8_tag.Component;
		}
		else
		{
			light = control_lite9_tag.Component;
			if (control_roll2_tag.Component != caller)
				light = control_lite10_tag.Component;
		}
		if (!light->FlasherActive)
		{
			if (light->BmpIndex1)
			{
				light->Message(20, 0.0);
			}
			else
			{
				light->Message(19, 0.0);
				int activeCount = control_bmpr_inc_lights_tag.Component->Message(37, 0.0);
				if (activeCount == control_bmpr_inc_lights_tag.Component->Message(38, 0.0))
				{
					control_bmpr_inc_lights_tag.Component->Message(7, 5.0);
					control_bmpr_inc_lights_tag.Component->Message(0, 0.0);
					if (control_bump1_tag.Component->BmpIndex < 3)
					{
						control_attack_bump_tag.Component->Message(12, 0.0);
						control_info_text_box_tag.Component->Display(pinball::get_rc_string(5, 0), 2.0, 2);
					}
					control_attack_bump_tag.Component->Message(48, 60.0);
				}
			}
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::BumperGroupControl(int code, TPinballComponent* caller)
{
	if (code == 61)
	{
		/*Bug in the original. Caller (TComponentGroup) is accessed beyond bounds at 0x4E*/
		if (static_cast<TBumper*>(caller)->BmpIndex)
		{
			caller->Message(48, 60.0);
			caller->Message(13, 0.0);
		}
	}
}

void control::LaunchLanesRolloverControl(int code, TPinballComponent* caller)
{
	TLight* light;

	if (code == 63)
	{
		if (control_roll112_tag.Component == caller)
		{
			light = control_lite171_tag.Component;
		}
		else
		{
			light = control_lite170_tag.Component;
			if (control_roll111_tag.Component != caller)
				light = control_lite169_tag.Component;
		}
		if (!light->FlasherActive)
		{
			if (light->BmpIndex1)
			{
				light->Message(20, 0.0);
			}
			else
			{
				light->Message(19, 0.0);
				int msg1 = control_ramp_bmpr_inc_lights_tag.Component->Message(37, 0.0);
				if (msg1 == control_ramp_bmpr_inc_lights_tag.Component->Message(38, 0.0))
				{
					control_ramp_bmpr_inc_lights_tag.Component->Message(7, 5.0);
					control_ramp_bmpr_inc_lights_tag.Component->Message(0, 0.0);
					if (control_bump5_tag.Component->BmpIndex < 3)
					{
						control_launch_bump_tag.Component->Message(12, 0.0);
						control_info_text_box_tag.Component->Display(pinball::get_rc_string(6, 0), 2.0, 2);
					}
					control_launch_bump_tag.Component->Message(48, 60.0);
				}
			}
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::OutLaneRolloverControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (light_on(&control_lite17_tag) || light_on(&control_lite18_tag))
		{
			table_add_extra_ball(2.0);
			control_lite17_tag.Component->Message(20, 0.0);
			control_lite18_tag.Component->Message(20, 0.0);
		}
		else
		{
			control_soundwave26_tag.Component->Play();
		}
		if (control_roll4_tag.Component == caller)
		{
			if (light_on(&control_lite30_tag))
			{
				control_lite30_tag.Component->Message(4, 0.0);
				control_lite196_tag.Component->Message(4, 0.0);
			}
		}
		else if (light_on(&control_lite29_tag))
		{
			control_lite29_tag.Component->Message(4, 0.0);
			control_lite195_tag.Component->Message(4, 0.0);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::ExtraBallLightControl(int code, TPinballComponent* caller)
{
	if (code == 19)
	{
		control_lite17_tag.Component->Message(9, 55.0);
		control_lite18_tag.Component->Message(9, 55.0);
		extraball_light_flag = 1;
	}
	else if (code == 60)
	{
		if (extraball_light_flag)
		{
			control_lite17_tag.Component->Message(7, 5.0);
			control_lite18_tag.Component->Message(7, 5.0);
			extraball_light_flag = 0;
		}
	}
}

void control::ReturnLaneRolloverControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_roll6_tag.Component == caller)
		{
			if (light_on(&control_lite27_tag))
			{
				control_lite59_tag.Component->Message(20, 0.0);
				control_lite27_tag.Component->Message(20, 0.0);
				TableG->AddScore(caller->get_scoring(1));
			}
			else
				TableG->AddScore(caller->get_scoring(0));
		}
		else if (control_roll7_tag.Component == caller)
		{
			if (light_on(&control_lite28_tag))
			{
				control_lite59_tag.Component->Message(20, 0.0);
				control_lite28_tag.Component->Message(20, 0.0);
				TableG->AddScore(caller->get_scoring(1));
			}
			else
				TableG->AddScore(caller->get_scoring(0));
		}
	}
}

void control::BonusLaneRolloverControl(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code == 63)
	{
		if (light_on(&control_lite16_tag))
		{
			int addedScore = SpecialAddScore(TableG->ScoreSpecial2);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(3, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			control_lite16_tag.Component->Message(20, 0.0);
			control_soundwave50_1_tag.Component->Play();
		}
		else
		{
			TableG->AddScore(caller->get_scoring(0));
			control_soundwave25_tag.Component->Play();
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		control_fuel_bargraph_tag.Component->Message(45, 11.0);
	}
}

void control::FuelRollover1Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_fuel_bargraph_tag.Component->Message(37, 0.0) > 1)
		{
			control_literoll179_tag.Component->Message(8, 0.05f);
		}
		else
		{
			control_fuel_bargraph_tag.Component->Message(45, 1.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::FuelRollover2Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_fuel_bargraph_tag.Component->Message(37, 0.0) > 3)
		{
			control_literoll180_tag.Component->Message(8, 0.05f);
		}
		else
		{
			control_fuel_bargraph_tag.Component->Message(45, 3.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::FuelRollover3Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_fuel_bargraph_tag.Component->Message(37, 0.0) > 5)
		{
			control_literoll181_tag.Component->Message(8, 0.05f);
		}
		else
		{
			control_fuel_bargraph_tag.Component->Message(45, 5.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::FuelRollover4Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_fuel_bargraph_tag.Component->Message(37, 0.0) > 7)
		{
			control_literoll182_tag.Component->Message(8, 0.05f);
		}
		else
		{
			control_fuel_bargraph_tag.Component->Message(45, 7.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::FuelRollover5Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_fuel_bargraph_tag.Component->Message(37, 0.0) > 9)
		{
			control_literoll183_tag.Component->Message(8, 0.05f);
		}
		else
		{
			control_fuel_bargraph_tag.Component->Message(45, 9.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::FuelRollover6Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (control_fuel_bargraph_tag.Component->Message(37, 0.0) > 11)
		{
			control_literoll184_tag.Component->Message(8, 0.05f);
		}
		else
		{
			control_fuel_bargraph_tag.Component->Message(45, 11.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::HyperspaceLightGroupControl(int code, TPinballComponent* caller)
{
	switch (code)
	{
	case 0:
		caller->Message(0, 0.0);
		break;
	case 41:
		caller->Message(41, 2.0);
		caller->Message(43, 60.0);
		break;
	case 61:
		caller->Message(33, 0.0);
		if (caller->Message(37, 0.0))
			caller->Message(43, 60.0);
		break;
	default: break;
	}
}

void control::WormHoleControl(int code, TPinballComponent* caller)
{
	int sinkFlag2;
	TSink* sink = static_cast<TSink*>(caller);

	if (code == 63)
	{
		int sinkFlag = 0;
		if (control_sink1_tag.Component != sink)
		{
			sinkFlag = control_sink2_tag.Component != sink;
			++sinkFlag;
		}

		int lite4Msg = control_lite4_tag.Component->MessageField;
		if (lite4Msg)
		{
			control_lite4_tag.Component->MessageField = 0;
			control_worm_hole_lights_tag.Component->Message(20, 0.0);
			control_bsink_arrow_lights_tag.Component->Message(20, 0.0);
			control_lite110_tag.Component->Message(20, 0.0);
			if (lite4Msg == sinkFlag + 1)
			{
				if (TableG->MultiballFlag)
				{
					table_bump_ball_sink_lock();
					TableG->AddScore(10000);
				}
				else
				{
					control_info_text_box_tag.Component->Display(pinball::get_rc_string(49, 0), 2.0, 2);
					table_set_replay(4.0);
					TableG->AddScore(sink->get_scoring(1));
					wormhole_tag_array2[sinkFlag]->GetComponent()->Message(16, sink->TimerTime);
					wormhole_tag_array3[sinkFlag]->GetComponent()->Message(11, static_cast<float>(2 - sinkFlag));
					wormhole_tag_array3[sinkFlag]->GetComponent()->Message(16, sink->TimerTime);
					wormhole_tag_array1[sinkFlag]->GetComponent()->Message(56, sink->TimerTime);
				}
				return;
			}
			TableG->AddScore(sink->get_scoring(2));
			sinkFlag2 = lite4Msg - 1;
		}
		else
		{
			TableG->AddScore(sink->get_scoring(0));
			sinkFlag2 = sinkFlag;
		}

		wormhole_tag_array2[sinkFlag2]->GetComponent()->Message(16, sink->TimerTime);
		wormhole_tag_array3[sinkFlag2]->GetComponent()->Message(11, static_cast<float>(2 - sinkFlag2));
		wormhole_tag_array3[sinkFlag2]->GetComponent()->Message(16, sink->TimerTime);
		wormhole_tag_array1[sinkFlag2]->GetComponent()->Message(56, sink->TimerTime);
		control_info_text_box_tag.Component->Display(pinball::get_rc_string(49, 0), 2.0, 2);
	}
}

void control::LeftFlipperControl(int code, TPinballComponent* caller)
{
	if (code == 1)
	{
		control_bmpr_inc_lights_tag.Component->Message(24, 0.0);
		control_ramp_bmpr_inc_lights_tag.Component->Message(24, 0.0);
	}
}

void control::RightFlipperControl(int code, TPinballComponent* caller)
{
	if (code == 1)
	{
		control_bmpr_inc_lights_tag.Component->Message(25, 0.0);
		control_ramp_bmpr_inc_lights_tag.Component->Message(25, 0.0);
	}
}

void control::JackpotLightControl(int code, TPinballComponent* caller)
{
	if (code == 60)
		TableG->ScoreSpecial3Flag = 0;
}

void control::BonusLightControl(int code, TPinballComponent* caller)
{
	if (code == 60)
		TableG->ScoreSpecial2Flag = 0;
}

void control::BoosterTargetControl(int code, TPinballComponent* caller)
{
	TSound* sound = nullptr;

	if (code == 63 && !caller->MessageField)
	{
		caller->MessageField = 1;
		if (control_target1_tag.Component->MessageField
			+ control_target2_tag.Component->MessageField
			+ control_target3_tag.Component->MessageField != 3)
		{
			TableG->AddScore(caller->get_scoring(0));
			return;
		}
		if (light_on(&control_lite61_tag))
		{
			if (light_on(&control_lite60_tag))
			{
				if (light_on(&control_lite59_tag))
				{
					if (light_on(&control_lite58_tag))
					{
						TableG->AddScore(caller->get_scoring(1));
					}
					else
					{
						table_set_bonus_hold();
					}
					sound = control_soundwave48_tag.Component;
				}
				else
				{
					table_set_bonus();
					sound = control_soundwave46_tag.Component;
				}
			}
			else
			{
				table_set_jackpot();
				sound = control_soundwave45_tag.Component;
			}
		}
		else
		{
			int msg = control_lite198_tag.Component->MessageField;
			if (msg != 15 && msg != 29)
			{
				table_set_flag_lights();
				sound = control_soundwave47_tag.Component;
			}
		}
		if (sound)
			sound->Play();

		control_target1_tag.Component->MessageField = 0;
		control_target1_tag.Component->Message(50, 0.0);
		control_target2_tag.Component->MessageField = 0;
		control_target2_tag.Component->Message(50, 0.0);
		control_target3_tag.Component->MessageField = 0;
		control_target3_tag.Component->Message(50, 0.0);
		TableG->AddScore(caller->get_scoring(1));
	}
}

void control::MedalLightGroupControl(int code, TPinballComponent* caller)
{
	switch (code)
	{
	case 0:
		caller->Message(0, 0.0);
		break;
	case 41:
		caller->Message(41, 2.0);
		caller->Message(43, 30.0);
		break;
	case 61:
		caller->Message(33, 0.0);
		if (caller->Message(37, 0.0))
			caller->Message(43, 30.0);
		break;
	default: break;
	}
}

void control::MultiplierLightGroupControl(int code, TPinballComponent* caller)
{
	switch (code)
	{
	case 0:
		caller->Message(0, 0.0);
		break;
	case 41:
		caller->Message(41, 2.0);
		caller->Message(43, 30.0);
		break;
	case 61:
		if (TableG->ScoreMultiplier)
			TableG->ScoreMultiplier = TableG->ScoreMultiplier - 1;
		caller->Message(33, 0.0);
		if (caller->Message(37, 0.0))
			caller->Message(43, 30.0);
		break;
	case 64:
		TableG->ScoreMultiplier = 4;
		caller->Message(19, 0.0);
		caller->Message(43, 30.0);
		control_info_text_box_tag.Component->Display(pinball::get_rc_string(59, 0), 2.0, 2);
		break;
	case 65:
		TableG->ScoreMultiplier = 0;
		caller->Message(20, 0.0);
		caller->Message(43, -1.0);
		break;
	default:
		break;
	}
}

void control::FuelSpotTargetControl(int code, TPinballComponent* caller)
{
	TPinballComponent* liteComp;

	if (code == 63)
	{
		if (control_target10_tag.Component == caller)
		{
			liteComp = control_lite70_tag.Component;
		}
		else
		{
			liteComp = control_lite71_tag.Component;
			if (control_target11_tag.Component != caller)
				liteComp = control_lite72_tag.Component;
		}
		liteComp->Message(15, 2.0);
		TableG->AddScore(caller->get_scoring(0));
		if (control_top_circle_tgt_lights_tag.Component->Message(37, 0.0) == 3)
		{
			control_top_circle_tgt_lights_tag.Component->Message(16, 2.0);
			control_fuel_bargraph_tag.Component->Message(45, 11.0);
			control_soundwave25_tag.Component->Play();
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(44, 0), 2.0, 2);
		}
		else
		{
			control_soundwave49D_tag.Component->Play();
		}
	}
}

void control::MissionSpotTargetControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		TPinballComponent* lite;
		if (control_target13_tag.Component == caller)
		{
			control_lite101_tag.Component->MessageField |= 1u;
			lite = control_lite101_tag.Component;
		}
		else if (control_target14_tag.Component == caller)
		{
			control_lite101_tag.Component->MessageField |= 2u;
			lite = control_lite102_tag.Component;
		}
		else
		{
			control_lite101_tag.Component->MessageField |= 4u;
			lite = control_lite103_tag.Component;
		}
		lite->Message(15, 2.0);

		TSound* sound;
		if (!light_on(&control_lite198_tag) || control_lite198_tag.Component->FlasherActive)
		{
			sound = control_soundwave52_tag.Component;
		}
		else
			sound = control_soundwave49D_tag.Component;
		sound->Play();
		TableG->AddScore(caller->get_scoring(0));
		if (control_ramp_tgt_lights_tag.Component->Message(37, 0.0) == 3)
			control_ramp_tgt_lights_tag.Component->Message(16, 2.0);
	}
}

void control::LeftHazardSpotTargetControl(int code, TPinballComponent* caller)
{
	TPinballComponent* lite;

	if (code == 63)
	{
		if (control_target16_tag.Component == caller)
		{
			control_lite104_tag.Component->MessageField |= 1u;
			lite = control_lite104_tag.Component;
		}
		else if (control_target17_tag.Component == caller)
		{
			control_lite104_tag.Component->MessageField |= 2u;
			lite = control_lite105_tag.Component;
		}
		else
		{
			control_lite104_tag.Component->MessageField |= 4u;
			lite = control_lite106_tag.Component;
		}
		lite->Message(15, 2.0);
		TableG->AddScore(caller->get_scoring(0));
		if (control_lchute_tgt_lights_tag.Component->Message(37, 0.0) == 3)
		{
			control_soundwave14_1_tag.Component->Play();
			control_gate1_tag.Component->Message(53, 0.0);
			control_lchute_tgt_lights_tag.Component->Message(16, 2.0);
		}
		else
		{
			control_soundwave49D_tag.Component->Play();
		}
	}
}

void control::RightHazardSpotTargetControl(int code, TPinballComponent* caller)
{
	TPinballComponent* light;

	if (code == 63)
	{
		if (control_target19_tag.Component == caller)
		{
			control_lite107_tag.Component->MessageField |= 1u;
			light = control_lite107_tag.Component;
		}
		else if (control_target20_tag.Component == caller)
		{
			control_lite107_tag.Component->MessageField |= 2u;
			light = control_lite108_tag.Component;
		}
		else
		{
			control_lite107_tag.Component->MessageField |= 4u;
			light = control_lite109_tag.Component;
		}
		light->Message(15, 2.0);
		TableG->AddScore(caller->get_scoring(0));
		if (control_bpr_solotgt_lights_tag.Component->Message(37, 0.0) == 3)
		{
			control_soundwave14_1_tag.Component->Play();
			control_gate2_tag.Component->Message(53, 0.0);
			control_bpr_solotgt_lights_tag.Component->Message(16, 2.0);
		}
		else
		{
			control_soundwave49D_tag.Component->Play();
		}
	}
}

void control::WormHoleDestinationControl(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (!light_on(&control_lite110_tag))
		{
			control_lite110_tag.Component->Message(15, 3.0);
			control_info_text_box_tag.Component->Display(pinball::get_rc_string(93, 0), 2.0, 2);
		}
		TableG->AddScore(caller->get_scoring(0));
		AdvanceWormHoleDestination(1);
	}
}

void control::BlackHoleKickoutControl(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code == 63)
	{
		int addedScore = TableG->AddScore(caller->get_scoring(0));
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(80, 0), addedScore);
		control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
		caller->Message(55, -1.0);
	}
}

void control::FlagControl(int code, TPinballComponent* caller)
{
	if (code == 62)
	{
		AdvanceWormHoleDestination(0);
	}
	else if (code == 63)
	{
		int score = caller->get_scoring(light_on(&control_lite20_tag));
		TableG->AddScore(score);
	}
}

void control::GravityWellKickoutControl(int code, TPinballComponent* caller)
{
	char Buffer[64];

	switch (code)
	{
	case 63:
		{
			auto addedScore = TableG->AddScore(caller->get_scoring(0));
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(81, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			control_lite62_tag.Component->Message(20, 0.0);
			caller->ActiveFlag = 0;
			auto duration = control_soundwave7_tag.Component->Play();
			caller->Message(55, duration);
			break;
		}
	case 64:
		{
			auto score = reinterpret_cast<size_t>(caller);
			if (score)
			{
				snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(82, 0), score);
			}
			else
			{
				snprintf(Buffer, sizeof Buffer, "%s", pinball::get_rc_string(45, 0));
			}
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			control_lite62_tag.Component->Message(4, 0.0);
			control_kickout1_tag.Component->ActiveFlag = 1;
			break;
		}
	case 1024:
		control_kickout1_tag.Component->ActiveFlag = 0;
		break;
	}
}

void control::SkillShotGate1Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		SpaceCadetPinballJNI::setBallInPlunger(false);
		control_lite200_tag.Component->Message(9, 5.0);
		if (light_on(&control_lite67_tag))
		{
			control_skill_shot_lights_tag.Component->Message(34, 0.0);
			control_skill_shot_lights_tag.Component->Message(20, 0.0);
			control_lite67_tag.Component->Message(19, 0.0);
			control_lite54_tag.Component->Message(7, 5.0);
			control_lite25_tag.Component->Message(7, 5.0);
			control_fuel_bargraph_tag.Component->Message(45, 11.0);
			control_soundwave14_2_tag.Component->Play();
		}
	}
}

void control::SkillShotGate2Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (light_on(&control_lite67_tag))
		{
			control_lite68_tag.Component->Message(19, 0.0);
			control_soundwave14_2_tag.Component->Play();
		}
	}
}

void control::SkillShotGate3Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (light_on(&control_lite67_tag))
		{
			control_lite69_tag.Component->Message(19, 0.0);
			control_soundwave14_2_tag.Component->Play();
		}
	}
}

void control::SkillShotGate4Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (light_on(&control_lite67_tag))
		{
			control_lite131_tag.Component->Message(19, 0.0);
			control_soundwave14_2_tag.Component->Play();
		}
	}
}

void control::SkillShotGate5Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (light_on(&control_lite67_tag))
		{
			control_lite132_tag.Component->Message(19, 0.0);
			control_soundwave14_2_tag.Component->Play();
		}
	}
}

void control::SkillShotGate6Control(int code, TPinballComponent* caller)
{
	if (code == 63)
	{
		if (light_on(&control_lite67_tag))
		{
			control_lite133_tag.Component->Message(19, 0.0);
			control_soundwave14_2_tag.Component->Play();
		}
	}
}

void control::ShootAgainLightControl(int code, TPinballComponent* caller)
{
	if (code == 60)
	{
		if (caller->MessageField)
		{
			caller->MessageField = 0;
		}
		else
		{
			caller->Message(16, 5.0);
			caller->MessageField = 1;
		}
	}
}

void control::EscapeChuteSinkControl(int code, TPinballComponent* caller)
{
	if (code == 63)
		caller->Message(56, static_cast<TSink*>(caller)->TimerTime);
}

void control::MissionControl(int code, TPinballComponent* caller)
{
	if (!control_lite198_tag.Component)
		return;

	int lite198Msg = control_lite198_tag.Component->MessageField;
	switch (code)
	{
	case 47:
		if (control_fuel_bargraph_tag.Component == caller && lite198Msg > 1)
		{
			control_l_trek_lights_tag.Component->Message(34, 0.0);
			control_l_trek_lights_tag.Component->Message(20, 0.0);
			control_r_trek_lights_tag.Component->Message(34, 0.0);
			control_r_trek_lights_tag.Component->Message(20, 0.0);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(109, 0), 4.0, 1);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
		}
		break;
	case 60:
		if (control_fuel_bargraph_tag.Component == caller && lite198Msg)
		{
			if (control_fuel_bargraph_tag.Component->Message(37, 0.0) == 1)
			{
				control_mission_text_box_tag.Component->Display(pinball::get_rc_string(116, 0), 4.0, 1);
			}
			break;
		}
		if (control_mission_text_box_tag.Component == caller)
			code = 67;
		break;
	case 1009:
		code = 67;
		break;
	default:
		break;
	}

	switch (lite198Msg)
	{
	case 0:
		WaitingDeploymentController(code, caller);
		break;
	case 1:
		SelectMissionController(code, caller);
		break;
	case 2:
		PracticeMissionController(code, caller);
		break;
	case 3:
		LaunchTrainingController(code, caller);
		break;
	case 4:
		ReentryTrainingController(code, caller);
		break;
	case 5:
		ScienceMissionController(code, caller);
		break;
	case 6:
		StrayCometController(code, caller);
		break;
	case 7:
		BlackHoleThreatController(code, caller);
		break;
	case 8:
		SpaceRadiationController(code, caller);
		break;
	case 9:
		BugHuntController(code, caller);
		break;
	case 10:
		AlienMenaceController(code, caller);
		break;
	case 11:
		RescueMissionController(code, caller);
		break;
	case 12:
		SatelliteController(code, caller);
		break;
	case 13:
		ReconnaissanceController(code, caller);
		break;
	case 14:
		DoomsdayMachineController(code, caller);
		break;
	case 15:
		CosmicPlagueController(code, caller);
		break;
	case 16:
		SecretMissionYellowController(code, caller);
		break;
	case 17:
		TimeWarpController(code, caller);
		break;
	case 18:
		MaelstromController(code, caller);
		break;
	case 20:
		AlienMenacePartTwoController(code, caller);
		break;
	case 21:
		CosmicPlaguePartTwoController(code, caller);
		break;
	case 22:
		SecretMissionRedController(code, caller);
		break;
	case 23:
		SecretMissionGreenController(code, caller);
		break;
	case 24:
		TimeWarpPartTwoController(code, caller);
		break;
	case 25:
		MaelstromPartTwoController(code, caller);
		break;
	case 26:
		MaelstromPartThreeController(code, caller);
		break;
	case 27:
		MaelstromPartFourController(code, caller);
		break;
	case 28:
		MaelstromPartFiveController(code, caller);
		break;
	case 29:
		MaelstromPartSixController(code, caller);
		break;
	case 30:
		MaelstromPartSevenController(code, caller);
		break;
	case 31:
		MaelstromPartEightController(code, caller);
		break;
	case 32:
		GameoverController(code, caller);
		break;
	default:
		UnselectMissionController(code, caller);
		break;
	}
}

void control::HyperspaceKickOutControl(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
		return;

	auto activeCount = control_hyper_lights_tag.Component->Message(37, 0.0);
	HyperspaceLightGroupControl(41, control_hyper_lights_tag.Component);
	switch (activeCount)
	{
	case 0:
		{
			auto addedScore = TableG->AddScore(caller->get_scoring(0));
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(12, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			break;
		}
	case 1:
		{
			auto addedScore = SpecialAddScore(TableG->ScoreSpecial3);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(14, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			TableG->ScoreSpecial3 = 20000;
			break;
		}
	case 2:
		{
			DrainBallBlockerControl(52, control_block1_tag.Component);
			auto addedScore = TableG->AddScore(caller->get_scoring(2));
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(2, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			break;
		}
	case 3:
		{
			ExtraBallLightControl(19, nullptr);
			auto addedScore = TableG->AddScore(caller->get_scoring(3));
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(8, 0), addedScore);
			control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
			break;
		}
	case 4:
		{
			control_hyper_lights_tag.Component->Message(0, 0.0);
			size_t addedScore = TableG->AddScore(caller->get_scoring(4));
			GravityWellKickoutControl(64, reinterpret_cast<TPinballComponent*>(addedScore));
			break;
		}
	default:
		break;
	}

	int someFlag = 0;
	if (light_on(&control_lite25_tag))
	{
		someFlag = 1;
		auto addedScore = SpecialAddScore(TableG->ScoreSpecial1);
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(10, 0), addedScore);
		control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
	}
	if (light_on(&control_lite26_tag))
		someFlag |= 2u;
	if (light_on(&control_lite130_tag))
	{
		someFlag |= 4u;
		control_lite130_tag.Component->Message(20, 0.0);
		MultiplierLightGroupControl(64, control_top_target_lights_tag.Component);
		control_bumber_target_lights_tag.Component->Message(19, 0.0);
		table_set_jackpot();
		table_set_bonus();
		table_set_flag_lights();
		table_set_bonus_hold();
		control_lite27_tag.Component->Message(19, 0.0);
		control_lite28_tag.Component->Message(19, 0.0);
		ExtraBallLightControl(19, nullptr);
		DrainBallBlockerControl(52, control_block1_tag.Component);

		if (TableG->MultiballFlag)
		{
			table_set_multiball();
		}
		if (TableG->ScoreSpecial3 < 100000)
			TableG->ScoreSpecial3 = 100000;
		if (TableG->ScoreSpecial2 < 100000)
			TableG->ScoreSpecial2 = 100000;
		GravityWellKickoutControl(64, nullptr);
	}

	TSound* sound;
	if (someFlag)
	{
		if (someFlag == 1)
		{
			sound = control_soundwave21_tag.Component;
		}
		else
		{
			if (someFlag < 1 || someFlag > 3)
			{
				auto duration = control_soundwave41_tag.Component->Play();
				control_soundwave36_1_tag.Component->Play();
				control_soundwave50_2_tag.Component->Play();
				control_lite25_tag.Component->Message(7, 5.0);
				caller->Message(55, duration);
				return;
			}
			sound = control_soundwave40_tag.Component;
		}
	}
	else
	{
		switch (activeCount)
		{
		case 1:
			sound = control_soundwave36_2_tag.Component;
			break;
		case 2:
			sound = control_soundwave35_2_tag.Component;
			break;
		case 3:
			sound = control_soundwave38_tag.Component;
			break;
		case 4:
			sound = control_soundwave39_tag.Component;
			break;
		default:
			sound = control_soundwave35_1_tag.Component;
			break;
		}
	}
	auto duration = sound->Play();
	control_lite25_tag.Component->Message(7, 5.0);
	caller->Message(55, duration);
}

void control::PlungerControl(int code, TPinballComponent* caller)
{
	if (code == 1015)
	{
		MissionControl(67, nullptr);
	}
	else if (code == 1016)
	{
		table_unlimited_balls = false;
		if (!control_middle_circle_tag.Component->Message(37, 0.0))
			control_middle_circle_tag.Component->Message(32, 0.0);
		if (!light_on(&control_lite200_tag))
		{
			control_skill_shot_lights_tag.Component->Message(20, 0.0);
			control_lite67_tag.Component->Message(19, 0.0);
			control_skill_shot_lights_tag.Component->Message(26, 0.25f);
			control_l_trek_lights_tag.Component->Message(20, 0.0);
			control_l_trek_lights_tag.Component->Message(32, 0.2f);
			control_l_trek_lights_tag.Component->Message(26, 0.2f);
			control_r_trek_lights_tag.Component->Message(20, 0.0);
			control_r_trek_lights_tag.Component->Message(32, 0.2f);
			control_r_trek_lights_tag.Component->Message(26, 0.2f);
			TableG->ScoreSpecial1 = 25000;
			MultiplierLightGroupControl(65, control_top_target_lights_tag.Component);
			control_fuel_bargraph_tag.Component->Message(19, 0.0);
			control_lite200_tag.Component->Message(19, 0.0);
			control_gate1_tag.Component->Message(53, 0.0);
			control_gate2_tag.Component->Message(53, 0.0);
		}
		control_lite200_tag.Component->MessageField = 0;
	}
}

void control::MedalTargetControl(int code, TPinballComponent* caller)
{
	if (code == 63 && !caller->MessageField)
	{
		caller->MessageField = 1;
		if (control_target6_tag.Component->MessageField
			+ control_target5_tag.Component->MessageField
			+ control_target4_tag.Component->MessageField == 3)
		{
			MedalLightGroupControl(41, control_bumber_target_lights_tag.Component);
			int activeCount = control_bumber_target_lights_tag.Component->Message(37, 0.0) - 1;
			char* text;
			switch (activeCount)
			{
			case 0:
				TableG->AddScore(caller->get_scoring(1));
				text = pinball::get_rc_string(53, 0);
				break;
			case 1:
				TableG->AddScore(caller->get_scoring(2));
				text = pinball::get_rc_string(54, 0);
				break;
			default:
				table_add_extra_ball(4.0);
				text = pinball::get_rc_string(55, 0);
				break;
			}
			control_info_text_box_tag.Component->Display(text, 2.0, 2);
			control_target6_tag.Component->MessageField = 0;
			control_target6_tag.Component->Message(50, 0.0);
			control_target5_tag.Component->MessageField = 0;
			control_target5_tag.Component->Message(50, 0.0);
			control_target4_tag.Component->MessageField = 0;
			control_target4_tag.Component->Message(50, 0.0);
			return;
		}
		TableG->AddScore(caller->get_scoring(0));
	}
}

void control::MultiplierTargetControl(int code, TPinballComponent* caller)
{
	if (code == 63 && !caller->MessageField)
	{
		caller->MessageField = 1;
		if (control_target9_tag.Component->MessageField
			+ control_target8_tag.Component->MessageField
			+ control_target7_tag.Component->MessageField == 3)
		{
			TableG->AddScore(caller->get_scoring(1));
			MultiplierLightGroupControl(41, control_top_target_lights_tag.Component);
			int activeCount = control_top_target_lights_tag.Component->Message(37, 0.0);
			char* text;
			switch (activeCount)
			{
			case 1:
				TableG->ScoreMultiplier = 1;
				text = pinball::get_rc_string(56, 0);
				break;
			case 2:
				TableG->ScoreMultiplier = 2;
				text = pinball::get_rc_string(57, 0);
				break;
			case 3:
				TableG->ScoreMultiplier = 3;
				text = pinball::get_rc_string(58, 0);
				break;
			default:
				TableG->ScoreMultiplier = 4;
				text = pinball::get_rc_string(59, 0);
				break;
			}

			control_info_text_box_tag.Component->Display(text, 2.0, 2);
			control_target9_tag.Component->MessageField = 0;
			control_target9_tag.Component->Message(50, 0.0);
			control_target8_tag.Component->MessageField = 0;
			control_target8_tag.Component->Message(50, 0.0);
			control_target7_tag.Component->MessageField = 0;
			control_target7_tag.Component->Message(50, 0.0);
		}
		else
		{
			TableG->AddScore(caller->get_scoring(0));
		}
	}
}

void control::BallDrainControl(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code == 60)
	{
		if (control_lite199_tag.Component->MessageField)
		{
			TableG->Message(1022, 0.0);
			if (pb::chk_highscore())
			{
				control_soundwave3_tag.Component->Play();
				TableG->LightGroup->Message(16, 3.0);
				char* v11 = pinball::get_rc_string(177, 0);
				control_mission_text_box_tag.Component->Display(v11, -1.0, 1);
			}
		}
		else
		{
			control_plunger_tag.Component->Message(1016, 0.0);
		}
	}
	else if (code == 63)
	{
		if (table_unlimited_balls)
		{
			control_drain_tag.Component->Message(1024, 0.0);
			control_sink3_tag.Component->Message(56, 0.0);
		}
		else
		{
			if (TableG->TiltLockFlag)
			{
				control_lite200_tag.Component->Message(20, 0.0);
				control_lite199_tag.Component->Message(20, 0.0);
			}
			if (light_on(&control_lite200_tag))
			{
				control_soundwave27_tag.Component->Play();
				control_lite200_tag.Component->Message(19, 0.0);
				control_info_text_box_tag.Component->Display(pinball::get_rc_string(96, 0), -1.0, 2);
				control_soundwave59_tag.Component->Play();
			}
			else if (light_on(&control_lite199_tag))
			{
				control_soundwave27_tag.Component->Play();
				control_lite199_tag.Component->Message(20, 0.0);
				control_lite200_tag.Component->Message(19, 0.0);
				control_info_text_box_tag.Component->Display(pinball::get_rc_string(95, 0), 2.0, 2);
				control_soundwave59_tag.Component->Play();
				--TableG->UnknownP78;
			}
			else if (TableG->UnknownP75)
			{
				control_soundwave27_tag.Component->Play();
				--TableG->UnknownP75;
			}
			else
			{
				if (!TableG->TiltLockFlag)
				{
					int time = SpecialAddScore(TableG->ScoreSpecial2);
					snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(94, 0), time);
					control_info_text_box_tag.Component->Display(Buffer, 2.0, 2);
				}
				if (TableG->ExtraBalls)
				{
					TableG->ExtraBalls--;

					char* shootAgainText;
					control_soundwave59_tag.Component->Play();
					switch (TableG->CurrentPlayer)
					{
					case 0:
						shootAgainText = pinball::get_rc_string(97, 0);
						break;
					case 1:
						shootAgainText = pinball::get_rc_string(98, 0);
						break;
					case 2:
						shootAgainText = pinball::get_rc_string(99, 0);
						break;
					default:
					case 3:
						shootAgainText = pinball::get_rc_string(100, 0);
						break;
					}
					control_info_text_box_tag.Component->Display(shootAgainText, -1.0, 2);
				}
				else
				{
					TableG->ChangeBallCount(TableG->BallCount - 1);
					if (TableG->CurrentPlayer + 1 != TableG->PlayerCount || TableG->BallCount)
					{
						TableG->Message(1021, 0.0);
						control_lite199_tag.Component->MessageField = 0;
					}
					else
					{
						control_lite199_tag.Component->MessageField = 1;
					}
					control_soundwave27_tag.Component->Play();
				}
				control_bmpr_inc_lights_tag.Component->Message(20, 0.0);
				control_ramp_bmpr_inc_lights_tag.Component->Message(20, 0.0);
				control_lite30_tag.Component->Message(20, 0.0);
				control_lite29_tag.Component->Message(20, 0.0);
				control_lite1_tag.Component->Message(20, 0.0);
				control_lite54_tag.Component->Message(20, 0.0);
				control_lite55_tag.Component->Message(20, 0.0);
				control_lite56_tag.Component->Message(20, 0.0);
				control_lite17_tag.Component->Message(20, 0.0);
				control_lite18_tag.Component->Message(20, 0.0);
				control_lite27_tag.Component->Message(20, 0.0);
				control_lite28_tag.Component->Message(20, 0.0);
				control_lite16_tag.Component->Message(20, 0.0);
				control_lite20_tag.Component->Message(20, 0.0);
				control_hyper_lights_tag.Component->Message(20, 0.0);
				control_lite25_tag.Component->Message(20, 0.0);
				control_lite26_tag.Component->Message(20, 0.0);
				control_lite130_tag.Component->Message(20, 0.0);
				control_lite19_tag.Component->Message(20, 0.0);
				control_worm_hole_lights_tag.Component->Message(20, 0.0);
				control_bsink_arrow_lights_tag.Component->Message(20, 0.0);
				control_l_trek_lights_tag.Component->Message(20, 0.0);
				control_r_trek_lights_tag.Component->Message(20, 0.0);
				control_lite60_tag.Component->Message(20, 0.0);
				control_lite59_tag.Component->Message(20, 0.0);
				control_lite61_tag.Component->Message(20, 0.0);
				control_bumber_target_lights_tag.Component->Message(20, 0.0);
				control_top_target_lights_tag.Component->Message(20, 0.0);
				control_top_circle_tgt_lights_tag.Component->Message(20, 0.0);
				control_ramp_tgt_lights_tag.Component->Message(20, 0.0);
				control_lchute_tgt_lights_tag.Component->Message(20, 0.0);
				control_bpr_solotgt_lights_tag.Component->Message(20, 0.0);
				control_lite110_tag.Component->Message(20, 0.0);
				control_skill_shot_lights_tag.Component->Message(20, 0.0);
				control_lite77_tag.Component->Message(20, 0.0);
				control_lite198_tag.Component->Message(20, 0.0);
				control_lite196_tag.Component->Message(20, 0.0);
				control_lite195_tag.Component->Message(20, 0.0);
				control_fuel_bargraph_tag.Component->Message(20, 0.0);
				control_fuel_bargraph_tag.Component->Message(1024, 0.0);
				GravityWellKickoutControl(1024, nullptr);
				control_lite62_tag.Component->Message(20, 0.0);
				control_lite4_tag.Component->MessageField = 0;
				control_lite101_tag.Component->MessageField = 0;
				control_lite102_tag.Component->MessageField = 0;
				control_lite103_tag.Component->MessageField = 0;
				control_ramp_tgt_lights_tag.Component->MessageField = 0;
				control_outer_circle_tag.Component->Message(34, 0.0);
				control_middle_circle_tag.Component->Message(34, 0.0);
				control_attack_bump_tag.Component->Message(1024, 0.0);
				control_launch_bump_tag.Component->Message(1024, 0.0);
				control_gate1_tag.Component->Message(1024, 0.0);
				control_gate2_tag.Component->Message(1024, 0.0);
				control_block1_tag.Component->Message(1024, 0.0);
				control_target1_tag.Component->Message(1024, 0.0);
				control_target2_tag.Component->Message(1024, 0.0);
				control_target3_tag.Component->Message(1024, 0.0);
				control_target6_tag.Component->Message(1024, 0.0);
				control_target5_tag.Component->Message(1024, 0.0);
				control_target4_tag.Component->Message(1024, 0.0);
				control_target9_tag.Component->Message(1024, 0.0);
				control_target8_tag.Component->Message(1024, 0.0);
				control_target7_tag.Component->Message(1024, 0.0);
				if (control_lite199_tag.Component->MessageField)
					control_lite198_tag.Component->MessageField = 32;
				else
					control_lite198_tag.Component->MessageField = 0;
				MissionControl(66, nullptr);
				TableG->Message(1012, 0.0);
				if (light_on(&control_lite58_tag))
					control_lite58_tag.Component->Message(20, 0.0);
				else
					TableG->ScoreSpecial2 = 25000;
			}
		}
	}
}


void control::table_control_handler(int code)
{
	if (loader::Lenient)
		return;
	if (code == 1011)
	{
		table_unlimited_balls = false;
		control_lite77_tag.Component->Message(7, 0.0);
	}
}


void control::AlienMenaceController(int code, TPinballComponent* caller)
{
	if (code != 11)
	{
		if (code == 66)
		{
			control_attack_bump_tag.Component->Message(11, 0.0);
			TPinballComponent* lTrekLight = control_l_trek_lights_tag.Component;
			control_l_trek_lights_tag.Component->Message(20, 0.0);
			lTrekLight->Message(32, 0.2f);
			lTrekLight->Message(26, 0.2f);
			TPinballComponent* rTrekLight = control_r_trek_lights_tag.Component;
			control_r_trek_lights_tag.Component->Message(20, 0.0);
			rTrekLight->Message(32, 0.2f);
			rTrekLight->Message(26, 0.2f);
			control_lite307_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(175, 0), -1.0, 1);
		return;
	}
	if (control_bump1_tag.Component == caller)
	{
		if (control_bump1_tag.Component->BmpIndex)
		{
			control_lite307_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 20;
			MissionControl(66, nullptr);
		}
	}
}

void control::AlienMenacePartTwoController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 8;
			control_l_trek_lights_tag.Component->Message(34, 0.0);
			control_l_trek_lights_tag.Component->Message(20, 0.0);
			control_r_trek_lights_tag.Component->Message(34, 0.0);
			control_r_trek_lights_tag.Component->Message(20, 0.0);
			control_lite308_tag.Component->Message(7, 0.0);
			control_lite311_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(107, 0),
		          control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_bump1_tag.Component == caller
		|| control_bump2_tag.Component == caller
		|| control_bump3_tag.Component == caller
		|| control_bump4_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite308_tag.Component->Message(20, 0.0);
			control_lite311_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(130, 0), 4.0, 1);
			int addedScore = SpecialAddScore(750000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(7))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::BlackHoleThreatController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code == 11)
	{
		if (control_bump5_tag.Component == caller)
			MissionControl(67, caller);
	}
	else if (code == 63)
	{
		if (control_kickout3_tag.Component == caller
			&& control_bump5_tag.Component->BmpIndex)
		{
			if (light_on(&control_lite316_tag))
				control_lite316_tag.Component->Message(20, 0.0);
			if (light_on(&control_lite314_tag))
				control_lite314_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(124, 0), 4.0, 1);
			int addedScore = SpecialAddScore(1000000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(8))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
	else
	{
		if (code == 66)
		{
			control_launch_bump_tag.Component->Message(11, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		if (control_bump5_tag.Component->BmpIndex)
		{
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(123, 0), -1.0, 1);
			if (light_on(&control_lite316_tag))
				control_lite316_tag.Component->Message(20, 0.0);
			if (!light_on(&control_lite314_tag))
			{
				control_lite314_tag.Component->Message(7, 0.0);
			}
		}
		else
		{
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(122, 0), -1.0, 1);
			if (light_on(&control_lite314_tag))
				control_lite314_tag.Component->Message(20, 0.0);
			if (!light_on(&control_lite316_tag))
			{
				control_lite316_tag.Component->Message(7, 0.0);
			}
		}
	}
}

void control::BugHuntController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 15;
			control_target1_tag.Component->MessageField = 0;
			control_target1_tag.Component->Message(50, 0.0);
			control_target2_tag.Component->MessageField = 0;
			control_target2_tag.Component->Message(50, 0.0);
			control_target3_tag.Component->MessageField = 0;
			control_target3_tag.Component->Message(50, 0.0);
			control_target6_tag.Component->MessageField = 0;
			control_target6_tag.Component->Message(50, 0.0);
			control_target5_tag.Component->MessageField = 0;
			control_target5_tag.Component->Message(50, 0.0);
			control_target4_tag.Component->MessageField = 0;
			control_target4_tag.Component->Message(50, 0.0);
			control_target9_tag.Component->MessageField = 0;
			control_target9_tag.Component->Message(50, 0.0);
			control_target8_tag.Component->MessageField = 0;
			control_target8_tag.Component->Message(50, 0.0);
			control_target7_tag.Component->MessageField = 0;
			control_target7_tag.Component->Message(50, 0.0);
			control_top_circle_tgt_lights_tag.Component->Message(20, 0.0);
			control_ramp_tgt_lights_tag.Component->Message(20, 0.0);
			control_lchute_tgt_lights_tag.Component->Message(20, 0.0);
			control_bpr_solotgt_lights_tag.Component->Message(20, 0.0);
			control_lite306_tag.Component->Message(7, 0.0);
			control_lite308_tag.Component->Message(7, 0.0);
			control_lite310_tag.Component->Message(7, 0.0);
			control_lite313_tag.Component->Message(7, 0.0);
			control_lite319_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(125, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_target1_tag.Component == caller
		|| control_target2_tag.Component == caller
		|| control_target3_tag.Component == caller
		|| control_target6_tag.Component == caller
		|| control_target5_tag.Component == caller
		|| control_target4_tag.Component == caller
		|| control_target9_tag.Component == caller
		|| control_target8_tag.Component == caller
		|| control_target7_tag.Component == caller
		|| control_target10_tag.Component == caller
		|| control_target11_tag.Component == caller
		|| control_target12_tag.Component == caller
		|| control_target13_tag.Component == caller
		|| control_target14_tag.Component == caller
		|| control_target15_tag.Component == caller
		|| control_target16_tag.Component == caller
		|| control_target17_tag.Component == caller
		|| control_target18_tag.Component == caller
		|| control_target19_tag.Component == caller
		|| control_target20_tag.Component == caller
		|| control_target21_tag.Component == caller
		|| control_target22_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite306_tag.Component->Message(20, 0.0);
			control_lite308_tag.Component->Message(20, 0.0);
			control_lite310_tag.Component->Message(20, 0.0);
			control_lite313_tag.Component->Message(20, 0.0);
			control_lite319_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(126, 0), 4.0, 1);
			int addedScore = SpecialAddScore(750000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(7))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::CosmicPlagueController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 75;
			control_lite20_tag.Component->Message(19, 0.0);
			control_lite19_tag.Component->Message(19, 0.0);
			control_lite305_tag.Component->Message(7, 0.0);
			control_lite312_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(139, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_flag1_tag.Component == caller || control_flag2_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite305_tag.Component->Message(20, 0.0);
			control_lite312_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 21;
			MissionControl(66, nullptr);
			control_lite20_tag.Component->Message(20, 0.0);
			control_lite19_tag.Component->Message(20, 0.0);
		}
	}
}

void control::CosmicPlaguePartTwoController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite310_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(140, 0), -1.0, 1);
		return;
	}
	if (control_roll9_tag.Component == caller)
	{
		control_lite310_tag.Component->Message(20, 0.0);
		control_lite198_tag.Component->MessageField = 1;
		MissionControl(66, nullptr);
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(141, 0), 4.0, 1);
		int addedScore = SpecialAddScore(1750000);
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
		if (!AddRankProgress(11))
		{
			control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
			control_soundwave9_tag.Component->Play();
		}
	}
}

void control::DoomsdayMachineController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 3;
			control_lite301_tag.Component->Message(7, 0.0);
			control_lite320_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(137, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_roll4_tag.Component == caller || control_roll8_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite301_tag.Component->Message(20, 0.0);
			control_lite320_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(138, 0), 4.0, 1);
			int addedScore = SpecialAddScore(1250000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(9))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::GameoverController(int code, TPinballComponent* caller)
{
	char Buffer[128];

	if (code == 66)
	{
		control_goal_lights_tag.Component->Message(20, 0.0);
		pb::mode_change(GameModes::GameOver);
		control_flip1_tag.Component->Message(1022, 0.0);
		control_flip2_tag.Component->Message(1022, 0.0);
		control_mission_text_box_tag.Component->MessageField = 0;
		return;
	}
	if (code != 67)
		return;

	int missionMsg = control_mission_text_box_tag.Component->MessageField;
	if (missionMsg & 0x100)
	{
		int playerId = missionMsg % 4;
		int playerScore = TableG->PlayerScores[playerId].ScoreStruct->Score;
		auto nextPlayerId = playerId + 1;
		if (playerScore >= 0)
		{
			const char* playerNScoreText = nullptr;
			switch (nextPlayerId)
			{
			case 1:
				playerNScoreText = pinball::get_rc_string(180, 0);
				break;
			case 2:
				playerNScoreText = pinball::get_rc_string(181, 0);
				break;
			case 3:
				playerNScoreText = pinball::get_rc_string(182, 0);
				break;
			case 4:
				playerNScoreText = pinball::get_rc_string(183, 0);
				break;
			default:
				break;
			}
			if (playerNScoreText != nullptr)
			{
				snprintf(Buffer, sizeof Buffer, playerNScoreText, playerScore);
				control_mission_text_box_tag.Component->Display(Buffer, 3.0, 1);
				int msgField = nextPlayerId == TableG->PlayerCount ? 0x200 : nextPlayerId | 0x100;
				control_mission_text_box_tag.Component->MessageField = msgField;
				return;
			}
		}
		control_mission_text_box_tag.Component->MessageField = 0x200;
	}

	if (missionMsg & 0x200)
	{
		int highscoreId = missionMsg % 5;
		int highScore = pb::highscore_table[highscoreId].Score;
		auto nextHidhscoreId = highscoreId + 1;
		if (highScore > 0)
		{
			const char* highScoreNText = nullptr;
			switch (nextHidhscoreId)
			{
			case 1:
				highScoreNText = pinball::get_rc_string(184, 0);
				break;
			case 2:
				highScoreNText = pinball::get_rc_string(185, 0);
				break;
			case 3:
				highScoreNText = pinball::get_rc_string(186, 0);
				break;
			case 4:
				highScoreNText = pinball::get_rc_string(187, 0);
				break;
			case 5:
				highScoreNText = pinball::get_rc_string(188, 0);
				break;
			default:
				break;
			}
			if (highScoreNText != nullptr)
			{
				snprintf(Buffer, sizeof Buffer, highScoreNText, highScore);
				control_mission_text_box_tag.Component->Display(Buffer, 3.0, 1);
				int msgField = nextHidhscoreId == 5 ? 0 : nextHidhscoreId | 0x200;
				control_mission_text_box_tag.Component->MessageField = msgField;
				return;
			}
		}
	}

	control_mission_text_box_tag.Component->MessageField = 0x100;
	control_mission_text_box_tag.Component->Display(pinball::get_rc_string(172, 0), 10.0, 1);
}

void control::LaunchTrainingController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite317_tag.Component->Message(7, 0.0);
			control_lite56_tag.Component->MessageField = 3;
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(110, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_ramp_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite317_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(111, 0), 4.0, 1);
			int addedScore = SpecialAddScore(500000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(6))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::MaelstromController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 3;
			control_lite303_tag.Component->Message(7, 0.0);
			control_lite309_tag.Component->Message(7, 0.0);
			control_lite315_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(148, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_target1_tag.Component == caller
		|| control_target2_tag.Component == caller
		|| control_target3_tag.Component == caller
		|| control_target6_tag.Component == caller
		|| control_target5_tag.Component == caller
		|| control_target4_tag.Component == caller
		|| control_target9_tag.Component == caller
		|| control_target8_tag.Component == caller
		|| control_target7_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite303_tag.Component->Message(20, 0.0);
			control_lite309_tag.Component->Message(20, 0.0);
			control_lite315_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 25;
			MissionControl(66, nullptr);
		}
	}
}

void control::MaelstromPartEightController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite130_tag.Component->Message(19, 0.0);
			control_lite304_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(155, 0), -1.0, 1);
		return;
	}
	if (control_kickout2_tag.Component == caller)
	{
		control_lite304_tag.Component->Message(20, 0.0);
		control_lite130_tag.Component->Message(20, 0.0);
		control_lite198_tag.Component->MessageField = 1;
		MissionControl(66, nullptr);
		int addedScore = SpecialAddScore(5000000);
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
		control_info_text_box_tag.Component->Display(pinball::get_rc_string(48, 0), 4.0, 2);
		if (!AddRankProgress(18))
		{
			control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
			control_soundwave9_tag.Component->Play();
		}
	}
}

void control::MaelstromPartFiveController(int code, TPinballComponent* caller)
{
	if (code != 63)
	{
		if (code == 66)
		{
			control_lite317_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(152, 0), -1.0, 1);
		return;
	}
	if (control_ramp_tag.Component == caller)
	{
		control_lite317_tag.Component->Message(20, 0.0);
		control_lite198_tag.Component->MessageField = 29;
		MissionControl(66, nullptr);
	}
}

void control::MaelstromPartFourController(int code, TPinballComponent* caller)
{
	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 0;
			control_lite318_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(151, 0), -1.0, 1);
		return;
	}
	if (control_roll184_tag.Component == caller)
	{
		control_lite318_tag.Component->Message(20, 0.0);
		control_lite198_tag.Component->MessageField = 28;
		MissionControl(66, nullptr);
	}
}

void control::MaelstromPartSevenController(int code, TPinballComponent* caller)
{
	if (code != 63)
	{
		if (code == 66)
		{
			AdvanceWormHoleDestination(1);
			control_sink1_tag.Component->Message(7, 0.0);
			control_sink2_tag.Component->Message(7, 0.0);
			control_sink3_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(154, 0), -1.0, 1);
		return;
	}
	if (control_sink1_tag.Component == caller
		|| control_sink2_tag.Component == caller
		|| control_sink3_tag.Component == caller)
	{
		control_lite198_tag.Component->MessageField = 31;
		MissionControl(66, nullptr);
	}
}

void control::MaelstromPartSixController(int code, TPinballComponent* caller)
{
	if (code != 63)
	{
		if (code == 66)
		{
			control_lite20_tag.Component->Message(19, 0.0);
			control_lite19_tag.Component->Message(19, 0.0);
			control_lite305_tag.Component->Message(7, 0.0);
			control_lite312_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(153, 0), -1.0, 1);
		return;
	}
	if (control_flag1_tag.Component == caller || control_flag2_tag.Component == caller)
	{
		control_lite305_tag.Component->Message(20, 0.0);
		control_lite312_tag.Component->Message(20, 0.0);
		control_lite198_tag.Component->MessageField = 30;
		MissionControl(66, nullptr);
		control_lite20_tag.Component->Message(20, 0.0);
		control_lite19_tag.Component->Message(20, 0.0);
	}
}

void control::MaelstromPartThreeController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 5;
			control_lite301_tag.Component->Message(7, 0.0);
			control_lite302_tag.Component->Message(7, 0.0);
			control_lite307_tag.Component->Message(7, 0.0);
			control_lite316_tag.Component->Message(7, 0.0);
			control_lite320_tag.Component->Message(7, 0.0);
			control_lite321_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(150, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_roll3_tag.Component == caller
		|| control_roll2_tag.Component == caller
		|| control_roll1_tag.Component == caller
		|| control_roll112_tag.Component == caller
		|| control_roll111_tag.Component == caller
		|| control_roll110_tag.Component == caller
		|| control_roll4_tag.Component == caller
		|| control_roll8_tag.Component == caller
		|| control_roll6_tag.Component == caller
		|| control_roll7_tag.Component == caller
		|| control_roll5_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite301_tag.Component->Message(20, 0.0);
			control_lite302_tag.Component->Message(20, 0.0);
			control_lite307_tag.Component->Message(20, 0.0);
			control_lite316_tag.Component->Message(20, 0.0);
			control_lite320_tag.Component->Message(20, 0.0);
			control_lite321_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 27;
			MissionControl(66, nullptr);
		}
	}
}

void control::MaelstromPartTwoController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 3;
			control_lite306_tag.Component->Message(7, 0.0);
			control_lite308_tag.Component->Message(7, 0.0);
			control_lite310_tag.Component->Message(7, 0.0);
			control_lite313_tag.Component->Message(7, 0.0);
			control_lite319_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(149, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_target10_tag.Component == caller
		|| control_target11_tag.Component == caller
		|| control_target12_tag.Component == caller
		|| control_target13_tag.Component == caller
		|| control_target14_tag.Component == caller
		|| control_target15_tag.Component == caller
		|| control_target16_tag.Component == caller
		|| control_target17_tag.Component == caller
		|| control_target18_tag.Component == caller
		|| control_target19_tag.Component == caller
		|| control_target20_tag.Component == caller
		|| control_target21_tag.Component == caller
		|| control_target22_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite306_tag.Component->Message(20, 0.0);
			control_lite308_tag.Component->Message(20, 0.0);
			control_lite310_tag.Component->Message(20, 0.0);
			control_lite313_tag.Component->Message(20, 0.0);
			control_lite319_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 26;
			MissionControl(66, nullptr);
		}
	}
}

void control::PracticeMissionController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite308_tag.Component->Message(7, 0.0);
			control_lite311_tag.Component->Message(7, 0.0);
			control_lite56_tag.Component->MessageField = 8;
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(107, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}

	if (control_bump1_tag.Component == caller
		|| control_bump2_tag.Component == caller
		|| control_bump3_tag.Component == caller
		|| control_bump4_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite308_tag.Component->Message(20, 0.0);
			control_lite311_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(108, 0), 4.0, 1);
			int addedScore = SpecialAddScore(500000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(6))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::ReconnaissanceController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 15;
			control_lite301_tag.Component->Message(7, 0.0);
			control_lite302_tag.Component->Message(7, 0.0);
			control_lite307_tag.Component->Message(7, 0.0);
			control_lite316_tag.Component->Message(7, 0.0);
			control_lite320_tag.Component->Message(7, 0.0);
			control_lite321_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(134, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_roll3_tag.Component == caller
		|| control_roll2_tag.Component == caller
		|| control_roll1_tag.Component == caller
		|| control_roll112_tag.Component == caller
		|| control_roll111_tag.Component == caller
		|| control_roll110_tag.Component == caller
		|| control_roll4_tag.Component == caller
		|| control_roll8_tag.Component == caller
		|| control_roll6_tag.Component == caller
		|| control_roll7_tag.Component == caller
		|| control_roll5_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, nullptr);
		}
		else
		{
			control_lite301_tag.Component->Message(20, 0.0);
			control_lite302_tag.Component->Message(20, 0.0);
			control_lite307_tag.Component->Message(20, 0.0);
			control_lite316_tag.Component->Message(20, 0.0);
			control_lite320_tag.Component->Message(20, 0.0);
			control_lite321_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(136, 0), 4.0, 1);
			int addedScore = SpecialAddScore(1250000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(9))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::ReentryTrainingController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 3;
			control_l_trek_lights_tag.Component->Message(20, 0.0);
			static_cast<TPinballComponent*>(control_l_trek_lights_tag.Component)->Message(32, 0.2f);
			static_cast<TPinballComponent*>(control_l_trek_lights_tag.Component)->Message(26, 0.2f);
			control_r_trek_lights_tag.Component->Message(20, 0.0);
			static_cast<TPinballComponent*>(control_r_trek_lights_tag.Component)->Message(32, 0.2f);
			static_cast<TPinballComponent*>(control_r_trek_lights_tag.Component)->Message(26, 0.2f);
			control_lite307_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(112, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_roll3_tag.Component == caller
		|| control_roll2_tag.Component == caller
		|| control_roll1_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite307_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(113, 0), 4.0, 1);
			int addedScore = SpecialAddScore(500000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(6))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::RescueMissionController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	switch (code)
	{
	case 63:
		{
			if (control_target1_tag.Component == caller
				|| control_target2_tag.Component == caller
				|| control_target3_tag.Component == caller)
			{
				MissionControl(67, caller);
				return;
			}
			if (control_kickout2_tag.Component != caller || !light_on(&control_lite20_tag))
				return;
			control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
			if (control_lite56_tag.Component->MessageField)
			{
				MissionControl(67, caller);
				return;
			}
			if (light_on(&control_lite303_tag))
				control_lite303_tag.Component->Message(20, 0.0);
			if (light_on(&control_lite304_tag))
				control_lite304_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(129, 0), 4.0, 1);
			int addedScore = SpecialAddScore(750000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(7))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
			break;
		}
	case 66:
		control_lite20_tag.Component->Message(20, 0.0);
		control_lite19_tag.Component->Message(20, 0.0);
		control_lite56_tag.Component->MessageField = 1;
		break;
	case 67:
		if (light_on(&control_lite20_tag))
		{
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(128, 0), -1.0, 1);
			if (light_on(&control_lite303_tag))
				control_lite303_tag.Component->Message(20, 0.0);
			if (!light_on(&control_lite304_tag))
			{
				control_lite304_tag.Component->Message(7, 0.0);
			}
		}
		else
		{
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(127, 0), -1.0, 1);
			if (light_on(&control_lite304_tag))
				control_lite304_tag.Component->Message(20, 0.0);
			if (!light_on(&control_lite303_tag))
			{
				control_lite303_tag.Component->Message(7, 0.0);
			}
		}
		break;
	default:
		break;
	}
}

void control::SatelliteController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 3;
			control_lite308_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(132, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_bump4_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite308_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(133, 0), 4.0, 1);
			int addedScore = SpecialAddScore(1250000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(9))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::ScienceMissionController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 9;
			control_target1_tag.Component->MessageField = 0;
			control_target1_tag.Component->Message(50, 0.0);
			control_target2_tag.Component->MessageField = 0;
			control_target2_tag.Component->Message(50, 0.0);
			control_target3_tag.Component->MessageField = 0;
			control_target3_tag.Component->Message(50, 0.0);
			control_target6_tag.Component->MessageField = 0;
			control_target6_tag.Component->Message(50, 0.0);
			control_target5_tag.Component->MessageField = 0;
			control_target5_tag.Component->Message(50, 0.0);
			control_target4_tag.Component->MessageField = 0;
			control_target4_tag.Component->Message(50, 0.0);
			control_target9_tag.Component->MessageField = 0;
			control_target9_tag.Component->Message(50, 0.0);
			control_target8_tag.Component->MessageField = 0;
			control_target8_tag.Component->Message(50, 0.0);
			control_target7_tag.Component->MessageField = 0;
			control_target7_tag.Component->Message(50, 0.0);
			control_lite303_tag.Component->Message(7, 0.0);
			control_lite309_tag.Component->Message(7, 0.0);
			control_lite315_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(114, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_target1_tag.Component == caller
		|| control_target2_tag.Component == caller
		|| control_target3_tag.Component == caller
		|| control_target6_tag.Component == caller
		|| control_target5_tag.Component == caller
		|| control_target4_tag.Component == caller
		|| control_target9_tag.Component == caller
		|| control_target8_tag.Component == caller
		|| control_target7_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite303_tag.Component->Message(20, 0.0);
			control_lite309_tag.Component->Message(20, 0.0);
			control_lite315_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(115, 0), 4.0, 1);
			int addedScore = SpecialAddScore(750000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(9))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
}

void control::SecretMissionGreenController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite6_tag.Component->Message(19, 0.0);
			control_lite2_tag.Component->Message(11, 1.0);
			control_lite2_tag.Component->Message(19, 0.0);
			control_lite2_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		char* v2 = pinball::get_rc_string(144, 0);
		control_mission_text_box_tag.Component->Display(v2, -1.0, 1);
		return;
	}
	if (control_sink2_tag.Component == caller)
	{
		control_lite198_tag.Component->MessageField = 1;
		MissionControl(66, nullptr);
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(145, 0), 4.0, 1);
		int addedScore = SpecialAddScore(1500000);
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
		if (!AddRankProgress(10))
		{
			control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
			control_soundwave9_tag.Component->Play();
		}
	}
}

void control::SecretMissionRedController(int code, TPinballComponent* caller)
{
	if (code != 63)
	{
		if (code == 66)
		{
			control_lite5_tag.Component->Message(19, 0.0);
			control_lite4_tag.Component->Message(11, 2.0);
			control_lite4_tag.Component->Message(19, 0.0);
			control_lite4_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(143, 0), -1.0, 1);
		return;
	}
	if (control_sink1_tag.Component == caller)
	{
		control_lite198_tag.Component->MessageField = 23;
		MissionControl(66, nullptr);
	}
}

void control::SecretMissionYellowController(int code, TPinballComponent* caller)
{
	if (code != 63)
	{
		if (code == 66)
		{
			control_worm_hole_lights_tag.Component->Message(20, 0.0);
			control_bsink_arrow_lights_tag.Component->Message(20, 0.0);
			control_bsink_arrow_lights_tag.Component->Message(23, 0.0);
			control_lite110_tag.Component->Message(20, 0.0);
			control_lite7_tag.Component->Message(19, 0.0);
			control_lite3_tag.Component->Message(11, 0.0);
			control_lite3_tag.Component->Message(19, 0.0);
			control_lite3_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(142, 0), -1.0, 1);
		return;
	}
	if (control_sink3_tag.Component == caller)
	{
		control_lite198_tag.Component->MessageField = 22;
		MissionControl(66, nullptr);
	}
}

void control::SelectMissionController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	switch (code)
	{
	case 45:
	case 47:
		if (control_fuel_bargraph_tag.Component != caller)
			return;
		MissionControl(67, caller);
		return;
	case 63:
		{
			int missionLevel = 0;
			if (control_target13_tag.Component == caller)
				missionLevel = 1;
			if (control_target14_tag.Component == caller)
				missionLevel = 2;
			if (control_target15_tag.Component == caller)
				missionLevel = 3;
			if (!missionLevel)
			{
				if (control_ramp_tag.Component == caller
					&& light_on(&control_lite56_tag)
					&& control_fuel_bargraph_tag.Component->Message(37, 0.0))
				{
					control_lite56_tag.Component->Message(20, 0.0);
					control_lite198_tag.Component->Message(19, 0.0);
					control_outer_circle_tag.Component->Message(26, -1.0);
					if (light_on(&control_lite317_tag))
						control_lite317_tag.Component->Message(20, 0.0);
					if (light_on(&control_lite318_tag))
						control_lite318_tag.Component->Message(20, 0.0);
					if (light_on(&control_lite319_tag))
						control_lite319_tag.Component->Message(20, 0.0);
					control_lite198_tag.Component->MessageField = control_lite56_tag.Component->MessageField;
					auto scoreId = control_lite56_tag.Component->MessageField - 2;
					MissionControl(66, nullptr);
					int addedScore = SpecialAddScore(mission_select_scores[scoreId]);
					snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(77, 0), addedScore);
					control_mission_text_box_tag.Component->Display(Buffer, 4.0, 1);
				}
				return;
			}

			if (control_lite101_tag.Component->MessageField == 7)
			{
				control_lite101_tag.Component->MessageField = 0;
				missionLevel = 4;
			}

			int missionId;
			auto activeCount = control_middle_circle_tag.Component->Message(37, 0.0);
			switch (activeCount)
			{
			case 1:
				switch (missionLevel)
				{
				case 1:
					missionId = 3;
					break;
				case 2:
					missionId = 4;
					break;
				case 3:
					missionId = 2;
					break;
				default:
					missionId = 5;
					break;
				}
				break;
			case 2:
			case 3:
				switch (missionLevel)
				{
				case 1:
					missionId = 9;
					break;
				case 2:
					missionId = 11;
					break;
				case 3:
					missionId = 10;
					break;
				default:
					missionId = 16;
					break;
				}
				break;
			case 4:
			case 5:
				switch (missionLevel)
				{
				case 1:
					missionId = 6;
					break;
				case 2:
					missionId = 8;
					break;
				case 3:
					missionId = 7;
					break;
				default:
					missionId = 15;
					break;
				}
				break;
			case 6:
			case 7:
				switch (missionLevel)
				{
				case 1:
					missionId = 12;
					break;
				case 2:
					missionId = 13;
					break;
				case 3:
					missionId = 14;
					break;
				default:
					missionId = 17;
					break;
				}
				break;
			case 8:
			case 9:
				switch (missionLevel)
				{
				case 1:
					missionId = 15;
					break;
				case 2:
					missionId = 16;
					break;
				case 3:
					missionId = 17;
					break;
				default:
					missionId = 18;
					break;
				}
				break;
			default:
				return;
			}
			control_lite56_tag.Component->MessageField = missionId;
			control_lite56_tag.Component->Message(15, 2.0);
			control_lite198_tag.Component->Message(4, 0.0);
			MissionControl(67, caller);
			return;
		}
	case 66:
		control_lite198_tag.Component->Message(20, 0.0);
		control_outer_circle_tag.Component->Message(34, 0.0);
		control_ramp_tgt_lights_tag.Component->Message(20, 0.0);
		control_lite56_tag.Component->MessageField = 0;
		control_lite101_tag.Component->MessageField = 0;
		control_l_trek_lights_tag.Component->Message(34, 0.0);
		control_l_trek_lights_tag.Component->Message(20, 0.0);
		control_r_trek_lights_tag.Component->Message(34, 0.0);
		control_r_trek_lights_tag.Component->Message(20, 0.0);
		control_goal_lights_tag.Component->Message(20, 0.0);
		control_worm_hole_lights_tag.Component->Message(20, 0.0);
		control_bsink_arrow_lights_tag.Component->Message(20, 0.0);
		break;
	case 67:
		break;
	default:
		return;
	}

	if (control_fuel_bargraph_tag.Component->Message(37, 0.0))
	{
		if (light_on(&control_lite56_tag))
		{
			auto missionText = pinball::
				get_rc_string(MissionRcArray[control_lite56_tag.Component->MessageField - 2], 1);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(106, 0), missionText);
			control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
			if (light_on(&control_lite318_tag))
				control_lite318_tag.Component->Message(20, 0.0);
			if (light_on(&control_lite319_tag))
				control_lite319_tag.Component->Message(20, 0.0);
			if (!light_on(&control_lite317_tag))
				control_lite317_tag.Component->Message(7, 0.0);
		}
		else
		{
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(104, 0), -1.0, 1);
			if (light_on(&control_lite317_tag))
				control_lite317_tag.Component->Message(20, 0.0);
			if (light_on(&control_lite318_tag))
				control_lite318_tag.Component->Message(20, 0.0);
			if (!light_on(&control_lite319_tag))
			{
				control_lite319_tag.Component->Message(7, 0.0);
			}
		}
	}
	else
	{
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(105, 0), -1.0, 1);
		if (light_on(&control_lite317_tag))
			control_lite317_tag.Component->Message(20, 0.0);
		if (light_on(&control_lite319_tag))
			control_lite319_tag.Component->Message(20, 0.0);
		if (!light_on(&control_lite318_tag))
		{
			control_lite318_tag.Component->Message(7, 0.0);
		}
	}
}

void control::SpaceRadiationController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code == 63)
	{
		if (control_target16_tag.Component == caller
			|| control_target17_tag.Component == caller
			|| control_target18_tag.Component == caller)
		{
			if (control_lite104_tag.Component->MessageField == 7)
			{
				control_lite104_tag.Component->MessageField = 15;
				control_bsink_arrow_lights_tag.Component->Message(7, 0.0);
				control_lite313_tag.Component->Message(20, 0.0);
				MissionControl(67, caller);
				AdvanceWormHoleDestination(1);
			}
		}
		else if ((control_sink1_tag.Component == caller
				|| control_sink2_tag.Component == caller
				|| control_sink3_tag.Component == caller)
			&& control_lite104_tag.Component->MessageField == 15)
		{
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(121, 0), 4.0, 1);
			int addedScore = SpecialAddScore(1000000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(8))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
	else
	{
		if (code == 66)
		{
			control_lchute_tgt_lights_tag.Component->Message(20, 0.0);
			control_lite104_tag.Component->MessageField = 0;
			control_lite313_tag.Component->Message(7, 0.0);
		}
		else if (code == 67)
		{
			char* text;
			if (control_lite104_tag.Component->MessageField == 15)
				text = pinball::get_rc_string(120, 0);
			else
				text = pinball::get_rc_string(176, 0);
			control_mission_text_box_tag.Component->Display(text, -1.0, 1);
		}
	}
}

void control::StrayCometController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code == 63)
	{
		if (control_target19_tag.Component == caller
			|| control_target20_tag.Component == caller
			|| control_target21_tag.Component == caller)
		{
			if (control_lite107_tag.Component->MessageField == 7)
			{
				control_lite306_tag.Component->Message(20, 0.0);
				control_lite304_tag.Component->Message(7, 0.0);
				control_lite107_tag.Component->MessageField = 15;
				MissionControl(67, caller);
			}
		}
		else if (control_kickout2_tag.Component == caller && control_lite107_tag.Component->MessageField == 15)
		{
			control_lite304_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
			control_mission_text_box_tag.Component->Display(pinball::get_rc_string(119, 0), 4.0, 1);
			int addedScore = SpecialAddScore(1000000);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(78, 0), addedScore);
			if (!AddRankProgress(8))
			{
				control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
				control_soundwave9_tag.Component->Play();
			}
		}
	}
	else
	{
		if (code == 66)
		{
			control_bpr_solotgt_lights_tag.Component->Message(20, 0.0);
			control_lite107_tag.Component->MessageField = 0;
			control_lite306_tag.Component->Message(7, 0.0);
		}
		else if (code == 67)
		{
			char* text;
			if (control_lite107_tag.Component->MessageField == 15)
				text = pinball::get_rc_string(118, 0);
			else
				text = pinball::get_rc_string(117, 0);
			control_mission_text_box_tag.Component->Display(text, -1.0, 1);
		}
	}
}

void control::TimeWarpController(int code, TPinballComponent* caller)
{
	char Buffer[64];

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite56_tag.Component->MessageField = 25;
			control_lite300_tag.Component->Message(7, 0.0);
			control_lite322_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(146, 0), control_lite56_tag.Component->MessageField);
		control_mission_text_box_tag.Component->Display(Buffer, -1.0, 1);
		return;
	}
	if (control_rebo1_tag.Component == caller
		|| control_rebo2_tag.Component == caller
		|| control_rebo3_tag.Component == caller
		|| control_rebo4_tag.Component == caller)
	{
		control_lite56_tag.Component->MessageField = control_lite56_tag.Component->MessageField - 1;
		if (control_lite56_tag.Component->MessageField)
		{
			MissionControl(67, caller);
		}
		else
		{
			control_lite300_tag.Component->Message(20, 0.0);
			control_lite322_tag.Component->Message(20, 0.0);
			control_lite198_tag.Component->MessageField = 24;
			MissionControl(66, nullptr);
		}
	}
}

void control::TimeWarpPartTwoController(int code, TPinballComponent* caller)
{
	char Buffer[64]{};

	if (code != 63)
	{
		if (code == 66)
		{
			control_lite55_tag.Component->Message(7, -1.0);
			control_lite26_tag.Component->Message(7, -1.0);
			control_lite304_tag.Component->Message(7, 0.0);
			control_lite317_tag.Component->Message(7, 0.0);
		}
		else if (code != 67)
		{
			return;
		}
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(147, 0), -1.0, 1);
		return;
	}
	if (control_kickout2_tag.Component == caller)
	{
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(47, 0), 4.0, 1);
		if (control_middle_circle_tag.Component->Message(37, 0.0) > 1)
		{
			control_middle_circle_tag.Component->Message(33, 5.0);
			int rank = control_middle_circle_tag.Component->Message(37, 0.0);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(174, 0), pinball::get_rc_string(RankRcArray[rank - 1], 1));
			control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
		}
	}
	else
	{
		if (control_ramp_tag.Component != caller)
			return;
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(46, 0), 4.0, 1);
		if (control_middle_circle_tag.Component->Message(37, 0.0) < 9)
		{
			int rank = control_middle_circle_tag.Component->Message(37, 0.0);
			control_middle_circle_tag.Component->Message(41, 5.0);
			snprintf(Buffer, sizeof Buffer, pinball::get_rc_string(173, 0), pinball::get_rc_string(RankRcArray[rank], 1));
		}
		if (!AddRankProgress(12) && Buffer[0])
		{
			control_mission_text_box_tag.Component->Display(Buffer, 8.0, 1);
			control_soundwave10_tag.Component->Play();
		}
	}
	SpecialAddScore(2000000);
	control_lite55_tag.Component->Message(20, 0.0);
	control_lite26_tag.Component->Message(20, 0.0);
	control_lite304_tag.Component->Message(20, 0.0);
	control_lite317_tag.Component->Message(20, 0.0);
	control_lite198_tag.Component->MessageField = 1;
	MissionControl(66, nullptr);
	// SpecialAddScore sets the score dirty flag. So next tick it will be redrawn.
}

void control::UnselectMissionController(int code, TPinballComponent* caller)
{
	control_lite198_tag.Component->MessageField = 1;
	MissionControl(66, nullptr);
}

void control::WaitingDeploymentController(int code, TPinballComponent* caller)
{
	switch (code)
	{
	case 63:
		if (control_oneway4_tag.Component == caller || control_oneway10_tag.Component == caller)
		{
			control_lite198_tag.Component->MessageField = 1;
			MissionControl(66, nullptr);
		}
		break;
	case 66:
		control_mission_text_box_tag.Component->Clear(1);
		waiting_deployment_flag = 0;
		break;
	case 67:
		control_mission_text_box_tag.Component->Display(pinball::get_rc_string(50, 0), -1.0, 1);
		break;
	default:
		break;
	}
}
