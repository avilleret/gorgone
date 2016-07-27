{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 2,
			"revision" : 3,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 269.0, 213.0, 682.0, 606.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-90",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 466.5, 694.0, 118.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "lfoWaveform"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-91",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 466.5, 721.5, 101.0, 22.0 ],
					"style" : "",
					"text" : "lfoWaveform $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-88",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 466.5, 633.0, 118.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "lfoSyncedPeriod"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-89",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 466.5, 660.5, 123.0, 22.0 ],
					"style" : "",
					"text" : "lfoSyncedPeriod $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-86",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 466.5, 569.0, 118.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "lfoFreeRate"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-87",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 466.5, 596.5, 96.0, 22.0 ],
					"style" : "",
					"text" : "lfoFreeRate $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-84",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 466.5, 505.5, 118.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "lfoSyncOrFree"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-85",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 466.5, 533.0, 112.0, 22.0 ],
					"style" : "",
					"text" : "lfoSyncOrFree $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-82",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 266.5, 931.0, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "filterResModDep"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-83",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 266.5, 958.5, 129.0, 22.0 ],
					"style" : "",
					"text" : "filterResModDep $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-80",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 266.5, 868.5, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "filterFreqModDe"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-81",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 266.5, 896.0, 122.0, 22.0 ],
					"style" : "",
					"text" : "filterFreqModDe $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-78",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 266.5, 808.0, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "hipassRes"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-79",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 266.5, 835.5, 99.0, 22.0 ],
					"style" : "",
					"text" : "hipassRes $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-76",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 265.0, 745.0, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "lowpassFreq"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-77",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 265.0, 772.5, 102.0, 22.0 ],
					"style" : "",
					"text" : "lowpassFreq $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-74",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 265.0, 685.5, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "filterType"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-75",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 265.0, 713.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "filterType $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-72",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 265.0, 624.5, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "bypassFilter"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-73",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 265.0, 652.0, 99.0, 22.0 ],
					"style" : "",
					"text" : "bypassFilter $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-70",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 265.0, 565.5, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "downsampModDept"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-71",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 265.0, 593.0, 144.0, 22.0 ],
					"style" : "",
					"text" : "downsampModDept $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-68",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 265.0, 505.5, 129.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "downsamp"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-69",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 265.0, 533.0, 91.0, 22.0 ],
					"style" : "",
					"text" : "downsamp $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-66",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 996.5, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "crushModDepth"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-67",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 1024.0, 120.0, 22.0 ],
					"style" : "",
					"text" : "crushModDepth $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-64",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 931.0, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "crush"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-65",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 958.5, 60.0, 22.0 ],
					"style" : "",
					"text" : "crush $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-62",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 868.5, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "driveModDepth"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-63",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 896.0, 117.0, 22.0 ],
					"style" : "",
					"text" : "driveModDepth $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-59",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 808.0, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "drive"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 835.5, 57.0, 22.0 ],
					"style" : "",
					"text" : "drive $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-57",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 745.0, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "dryWetLink"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 772.5, 94.0, 22.0 ],
					"style" : "",
					"text" : "dryWetLink $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-55",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 685.5, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "bypassWetSignal"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-56",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 713.0, 129.0, 22.0 ],
					"style" : "",
					"text" : "bypassWetSignal $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-53",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 624.5, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "bypassDrySignal"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-54",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 652.0, 132.0, 22.0 ],
					"style" : "",
					"text" : "bypassDrySignal $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-52",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 565.5, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "wet"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-51",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 593.0, 49.0, 22.0 ],
					"style" : "",
					"text" : "wet $1"
				}

			}
, 			{
				"box" : 				{
					"floatoutput" : 1,
					"id" : "obj-49",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 17.0, 505.5, 117.0, 18.0 ],
					"size" : 1.0,
					"style" : "",
					"varname" : "dry"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 533.0, 47.0, 22.0 ],
					"style" : "",
					"text" : "dry $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 73.5, 351.0, 38.0, 22.0 ],
					"style" : "",
					"text" : "write"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-50",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 289.0, 448.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "recall 1 2 $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-48",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 289.0, 408.0, 43.0, 22.0 ],
					"style" : "",
					"text" : "/ 100."
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-47",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 289.0, 375.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 265.0, 331.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-37",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 183.0, 377.0, 57.0, 22.0 ],
					"style" : "",
					"text" : "store $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 175.0, 331.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"autosave" : 1,
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 8,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "signal", "signal", "", "list", "int", "", "", "" ],
					"patching_rect" : [ 17.0, 1145.5, 300.0, 100.0 ],
					"presentation_rect" : [ 0.0, 0.0, 300.0, 100.0 ],
					"save" : [ "#N", "vst~", "loaduniqueid", 0, ";" ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_invisible" : 1,
							"parameter_longname" : "amxd~[3]",
							"parameter_shortname" : "amxd~",
							"parameter_type" : 3
						}

					}
,
					"saved_object_attributes" : 					{
						"annotation_name" : "",
						"parameter_enable" : 1
					}
,
					"snapshot" : 					{
						"filetype" : "C74Snapshot",
						"version" : 2,
						"minorversion" : 0,
						"name" : "snapshotlist",
						"origin" : "vst~",
						"type" : "list",
						"subtype" : "Undefined",
						"embed" : 1,
						"snapshot" : 						{
							"pluginname" : "Krush.vst",
							"plugindisplayname" : "Krush",
							"pluginsavedname" : "Krush",
							"pluginsaveduniqueid" : 0,
							"version" : 1,
							"isbank" : 0,
							"isbase64" : 1,
							"sliderorder" : [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 ],
							"slidervisibility" : [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ],
							"blob" : "1125.CMlaKA....fQPMDZ....AP2ZKIG...vY....APTYlEVcrQG..............................PPJVMjLg.BA...OKIWcygFHvwVcmklaEQVZz8lbWkFYzgVOhzRLh.BbrU2Yo4VQjkFcuIGRkk1YnQWOhzRLh.RZy0TZjkVQtElXrUFY8HBLh.RZy0TZjkFTx81YxEVaCgVXtcVYE4VXhwVYj0iHvHBHiMVSoQVZCgVXt0iHvHhO7jjSSQUPNMTQPIUQFM0K9viQR8jVE4DTAIUPMMEHjIWd8HBLh.xckQWOh.iHfHVdvE1byQjb4MUZm4VXr0iHvHBHhkGbgM2bWUFcSk1YtEFa8HBLh.BYxk2UkQGSo41Z8HBLh.BYxklck0iHvHBHjIWZ1UVSuQFQkAGcn0iHvHBHiIWcygVOh.iHfLlb0MGZM8FYDUFbzgVOh.iHfP1a241bg0Fb8HBLh.BYucmayEVav0zajQTYvQGZ8HBLh.hX4AWXyMmQowFckIWOh.iHfXVZrQWYxQUdvUVOh.iHfv1a2AWXyMmQxUVb8HBLh.BaucGbgM2bRU1b8HBLh.BZoAWXyMmQxUVb8HBLh.BZoAWXyMmTkMWOh.iHfXVZrQWYxYjbkEWSuQFQkAGcn0iHvHBHlkFazUlbRU1bM8FYDUFbzgVOh.iHfvlYuMUdtM1SxYjbkUVOh.iHfvlYuYjbkUlTgQWY8HBLh.Bal81T441XkQFTkIWZuQVOh.iHfvlYucUX1UlYuIWa8HBLh7hO7.UPRETSSABYxkWOhDiK0HBH2UFc8HRKv3xMzPSLwHyMy.CLxXiLzTSLwbSL4HBHhkGbgM2bDIWdSk1YtEFa8HRLh.hX4AWXyM2UkQ2ToclagwVOhDiHfPlb4cUYzwTZtsVOh.iHfPlboYWY8HBLh.BYxklck0zajQTYvQGZ8HBLh.xXxU2bn0iHvHBHiIWcygVSuQFQkAGcn0iHvHBHj81ctMWXsAWOh.iHfP1a241bg0FbM8FYDUFbzgVOh.iHfHVdvE1byYTZrQWYx0iHvHBHlkFazUlbTkGbk0iHvHBHr81cvE1byYjbkEWOhHCLt.SMyLiLybCM0biL2TyL4.iMxHBHr81cvE1byIUYy0iHvHBHnkFbgM2bFIWYw0iHx.iHffVZvE1byIUYy0iHvHBHlkFazUlbFIWYw0zajQTYvQGZ8HBLh.hYowFckImTkMWSuQFQkAGcn0iHvHBHrY1aSkmai8jbFIWYk0iHvHBHrY1aFIWYkIUXzUVOh.iHfvlYuMUdtMVYjAUYxk1aj0iHvHBHrY1aWElckY1ax0VOh.iHu3COPEjTA0zTLE1bzwzagQVYjAkbkMWYzABbxU1bkQWOhHBHjklbzkWOhDiHu3COMkDQI0TPPAURNczK9vSSIQTRMEDTPkjSGwTXyQGSuEFYkQFTxU1bkQGHvIWYyUFc8HhHfPVZxQWd8HBLh7hO77xRxU2bn4C.^šƒ"
						}
,
						"snapshotlist" : 						{
							"current_snapshot" : 0,
							"entries" : [ 								{
									"filetype" : "C74Snapshot",
									"version" : 2,
									"minorversion" : 0,
									"name" : "Krush",
									"origin" : "Krush.vst",
									"type" : "VST",
									"subtype" : "MidiEffect",
									"embed" : 0,
									"snapshot" : 									{
										"pluginname" : "Krush.vst",
										"plugindisplayname" : "Krush",
										"pluginsavedname" : "Krush",
										"pluginsaveduniqueid" : 0,
										"version" : 1,
										"isbank" : 0,
										"isbase64" : 1,
										"sliderorder" : [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 ],
										"slidervisibility" : [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ],
										"blob" : "1125.CMlaKA....fQPMDZ....AP2ZKIG...vY....APTYlEVcrQG..............................PPJVMjLg.BA...OKIWcygFHvwVcmklaEQVZz8lbWkFYzgVOhzRLh.BbrU2Yo4VQjkFcuIGRkk1YnQWOhzRLh.RZy0TZjkVQtElXrUFY8HBLh.RZy0TZjkFTx81YxEVaCgVXtcVYE4VXhwVYj0iHvHBHiMVSoQVZCgVXt0iHvHhO7jjSSQUPNMTQPIUQFM0K9viQR8jVE4DTAIUPMMEHjIWd8HBLh.xckQWOh.iHfHVdvE1byQjb4MUZm4VXr0iHvHBHhkGbgM2bWUFcSk1YtEFa8HBLh.BYxk2UkQGSo41Z8HBLh.BYxklck0iHvHBHjIWZ1UVSuQFQkAGcn0iHvHBHiIWcygVOh.iHfLlb0MGZM8FYDUFbzgVOh.iHfP1a241bg0Fb8HBLh.BYucmayEVav0zajQTYvQGZ8HBLh.hX4AWXyMmQowFckIWOh.iHfXVZrQWYxQUdvUVOh.iHfv1a2AWXyMmQxUVb8HBLh.BaucGbgM2bRU1b8HBLh.BZoAWXyMmQxUVb8HBLh.BZoAWXyMmTkMWOh.iHfXVZrQWYxYjbkEWSuQFQkAGcn0iHvHBHlkFazUlbRU1bM8FYDUFbzgVOh.iHfvlYuMUdtM1SxYjbkUVOh.iHfvlYuYjbkUlTgQWY8HBLh.Bal81T441XkQFTkIWZuQVOh.iHfvlYucUX1UlYuIWa8HBLh7hO7.UPRETSSABYxkWOhDiK0HBH2UFc8HRKv3xMzPSLwHyMy.CLxXiLzTSLwbSL4HBHhkGbgM2bDIWdSk1YtEFa8HRLh.hX4AWXyM2UkQ2ToclagwVOhDiHfPlb4cUYzwTZtsVOh.iHfPlboYWY8HBLh.BYxklck0zajQTYvQGZ8HBLh.xXxU2bn0iHvHBHiIWcygVSuQFQkAGcn0iHvHBHj81ctMWXsAWOh.iHfP1a241bg0FbM8FYDUFbzgVOh.iHfHVdvE1byYTZrQWYx0iHvHBHlkFazUlbTkGbk0iHvHBHr81cvE1byYjbkEWOhHCLt.SMyLiLybCM0biL2TyL4.iMxHBHr81cvE1byIUYy0iHvHBHnkFbgM2bFIWYw0iHx.iHffVZvE1byIUYy0iHvHBHlkFazUlbFIWYw0zajQTYvQGZ8HBLh.hYowFckImTkMWSuQFQkAGcn0iHvHBHrY1aSkmai8jbFIWYk0iHvHBHrY1aFIWYkIUXzUVOh.iHfvlYuMUdtMVYjAUYxk1aj0iHvHBHrY1aWElckY1ax0VOh.iHu3COPEjTA0zTLE1bzwzagQVYjAkbkMWYzABbxU1bkQWOhHBHjklbzkWOhDiHu3COMkDQI0TPPAURNczK9vSSIQTRMEDTPkjSGwTXyQGSuEFYkQFTxU1bkQGHvIWYyUFc8HhHfPVZxQWd8HBLh7hO77xRxU2bn4C.^šƒ"
									}
,
									"fileref" : 									{
										"name" : "Krush",
										"filename" : "Krush_20160726.maxsnap",
										"filepath" : "~/Documents/Max 7/Snapshots",
										"filepos" : -1,
										"snapshotfileid" : "cf09a1ccee1ab985c8f9ea3d8a997aef"
									}

								}
 ]
						}

					}
,
					"style" : "",
					"text" : "vst~",
					"varname" : "amxd~",
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-43",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 424.5, 216.5, 130.0, 25.0 ],
					"style" : "",
					"text" : "Adjust its position."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-42",
					"maxclass" : "number",
					"maximum" : 720,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 373.75, 220.5, 50.0, 21.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-32",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 546.25, 19.0, 62.0, 23.0 ],
					"restore" : 					{
						"amxd~" : [ 							{
								"filetype" : "C74Snapshot",
								"version" : 2,
								"minorversion" : 0,
								"name" : "Krush",
								"origin" : "Krush.vst",
								"type" : "VST",
								"subtype" : "MidiEffect",
								"embed" : 1,
								"snapshot" : 								{
									"pluginname" : "Krush.vst",
									"plugindisplayname" : "Krush",
									"pluginsavedname" : "Krush",
									"pluginsaveduniqueid" : 0,
									"version" : 1,
									"isbank" : 0,
									"isbase64" : 1,
									"sliderorder" : [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 ],
									"slidervisibility" : [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ],
									"blob" : "1125.CMlaKA....fQPMDZ....AP2ZKIG...vY....APTYlEVcrQG..............................PPJVMjLg.BA...OKIWcygFHvwVcmklaEQVZz8lbWkFYzgVOhzRLh.BbrU2Yo4VQjkFcuIGRkk1YnQWOhzRLh.RZy0TZjkVQtElXrUFY8HBLh.RZy0TZjkFTx81YxEVaCgVXtcVYE4VXhwVYj0iHvHBHiMVSoQVZCgVXt0iHvHhO7jjSSQUPNMTQPIUQFM0K9viQR8jVE4DTAIUPMMEHjIWd8HBLh.xckQWOh.iHfHVdvE1byQjb4MUZm4VXr0iHvHBHhkGbgM2bWUFcSk1YtEFa8HBLh.BYxk2UkQGSo41Z8HBLh.BYxklck0iHvHBHjIWZ1UVSuQFQkAGcn0iHvHBHiIWcygVOh.iHfLlb0MGZM8FYDUFbzgVOh.iHfP1a241bg0Fb8HBLh.BYucmayEVav0zajQTYvQGZ8HBLh.hX4AWXyMmQowFckIWOh.iHfXVZrQWYxQUdvUVOh.iHfv1a2AWXyMmQxUVb8HBLh.BaucGbgM2bRU1b8HBLh.BZoAWXyMmQxUVb8HBLh.BZoAWXyMmTkMWOh.iHfXVZrQWYxYjbkEWSuQFQkAGcn0iHvHBHlkFazUlbRU1bM8FYDUFbzgVOh.iHfvlYuMUdtM1SxYjbkUVOh.iHfvlYuYjbkUlTgQWY8HBLh.Bal81T441XkQFTkIWZuQVOh.iHfvlYucUX1UlYuIWa8HBLh7hO7.UPRETSSABYxkWOhDiK0HBH2UFc8HRKv3xMzPSLwHyMy.CLxXiLzTSLwbSL4HBHhkGbgM2bDIWdSk1YtEFa8HRLh.hX4AWXyM2UkQ2ToclagwVOhDiHfPlb4cUYzwTZtsVOh.iHfPlboYWY8HBLh.BYxklck0zajQTYvQGZ8HBLh.xXxU2bn0iHvHBHiIWcygVSuQFQkAGcn0iHvHBHj81ctMWXsAWOh.iHfP1a241bg0FbM8FYDUFbzgVOh.iHfHVdvE1byYTZrQWYx0iHvHBHlkFazUlbTkGbk0iHvHBHr81cvE1byYjbkEWOhHCLt.SMyLiLybCM0biL2TyL4.iMxHBHr81cvE1byIUYy0iHvHBHnkFbgM2bFIWYw0iHx.iHffVZvE1byIUYy0iHvHBHlkFazUlbFIWYw0zajQTYvQGZ8HBLh.hYowFckImTkMWSuQFQkAGcn0iHvHBHrY1aSkmai8jbFIWYk0iHvHBHrY1aFIWYkIUXzUVOh.iHfvlYuMUdtMVYjAUYxk1aj0iHvHBHrY1aWElckY1ax0VOh.iHu3COPEjTA0zTLE1bzwzagQVYjAkbkMWYzABbxU1bkQWOhHBHjklbzkWOhDiHu3COMkDQI0TPPAURNczK9vSSIQTRMEDTPkjSGwTXyQGSuEFYkQFTxU1bkQGHvIWYyUFc8HhHfPVZxQWd8HBLh7hO77xRxU2bn4C."
								}

							}
 ],
						"bypassDrySignal" : [ 0.57476 ],
						"bypassFilter" : [ 0.0 ],
						"bypassWetSignal" : [ 0.75 ],
						"crush" : [ 0.0 ],
						"crushModDepth" : [ 0.0 ],
						"downsamp" : [ 0.0 ],
						"downsampModDept" : [ 0.0 ],
						"drive" : [ 0.0 ],
						"driveModDepth" : [ 0.0 ],
						"dry" : [ 0.75 ],
						"dryWetLink" : [ 0.0 ],
						"filterFreqModDe" : [ 0.0 ],
						"filterResModDep" : [ 0.0 ],
						"filterType" : [ 0.0 ],
						"hipassRes" : [ 0.0 ],
						"lfoFreeRate" : [ 0.0 ],
						"lfoSyncOrFree" : [ 0.0 ],
						"lfoSyncedPeriod" : [ 0.0 ],
						"lfoWaveform" : [ 0.0 ],
						"lowpassFreq" : [ 0.0 ],
						"wet" : [ 0.715998 ]
					}
,
					"style" : "",
					"text" : "autopattr",
					"varname" : "u420007445"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-30",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 443.25, 334.0, 187.5, 40.0 ],
					"style" : "",
					"text" : "Enable/disable patcher hierarchical display."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 421.5, 344.0, 20.0, 20.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-24",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 411.5, 374.0, 42.0, 21.0 ],
					"style" : "",
					"text" : "flat $1"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-20",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 517.75, 406.5, 132.0, 25.0 ],
					"style" : "",
					"text" : "Close the window."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-21",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 426.75, 409.5, 91.0, 23.0 ],
					"style" : "",
					"text" : "storage_close"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 373.75, 278.5, 35.0, 21.0 ],
					"style" : "",
					"text" : "pack"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 399.75, 251.5, 40.0, 21.0 ],
					"style" : "",
					"text" : "+ 300"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-12",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 373.75, 302.5, 139.0, 21.0 ],
					"style" : "",
					"text" : "storage_rect $1 $1 $2 $2"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-13",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 447.25, 184.0, 167.0, 25.0 ],
					"style" : "",
					"text" : "Open a storage window."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-14",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 349.25, 187.0, 97.0, 23.0 ],
					"style" : "",
					"text" : "storagewindow"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-4",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 131.5, 284.0, 154.0, 25.0 ],
					"style" : "",
					"text" : "Close the window."
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 90.5, 163.5, 130.0, 25.0 ],
					"style" : "",
					"text" : "Adjust its position."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 39.0, 225.5, 35.0, 21.0 ],
					"style" : "",
					"text" : "pack"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-27",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 65.0, 198.5, 40.0, 21.0 ],
					"style" : "",
					"text" : "+ 300"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-25",
					"maxclass" : "number",
					"maximum" : 720,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 39.0, 168.5, 50.0, 21.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 39.0, 249.5, 128.0, 21.0 ],
					"style" : "",
					"text" : "client_rect $1 $1 $2 $2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-18",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 53.5, 286.0, 78.0, 23.0 ],
					"style" : "",
					"text" : "client_close"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-39",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 101.0, 125.0, 154.0, 25.0 ],
					"style" : "",
					"text" : "Open a client window."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-38",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 128.0, 84.0, 23.0 ],
					"style" : "",
					"text" : "clientwindow"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-33",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 437.5, 233.0, 23.0 ],
					"saved_object_attributes" : 					{
						"client_rect" : [ 1057, 45, 1440, 407 ],
						"parameter_enable" : 0,
						"storage_rect" : [ 583, 69, 1034, 197 ]
					}
,
					"style" : "",
					"text" : "pattrstorage gorgone_1 @savemode 3",
					"varname" : "gorgone_1"
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-1",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 226.5, 163.5, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "2",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-31",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 657.5, 406.5, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "7",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-5",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 293.0, 286.0, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "3",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-22",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 635.25, 344.0, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "6",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-34",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 262.5, 125.0, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "1",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-16",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 564.25, 219.5, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "5",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"background" : 1,
					"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
					"fontface" : 1,
					"hint" : "",
					"id" : "obj-17",
					"ignoreclick" : 1,
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 618.75, 185.0, 20.0, 20.0 ],
					"rounded" : 60.0,
					"style" : "",
					"text" : "4",
					"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 383.25, 423.0, 26.5, 423.0 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 358.75, 423.0, 26.5, 423.0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 63.0, 423.0, 26.5, 423.0 ],
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 436.25, 435.0, 108.0, 435.0, 108.0, 423.0, 26.5, 423.0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 431.0, 366.0, 421.0, 366.0 ],
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 421.0, 396.0, 26.5, 396.0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 48.5, 192.0, 74.5, 192.0 ],
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 48.5, 192.0, 48.5, 192.0 ],
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 48.5, 273.0, 26.5, 273.0 ],
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 74.5, 222.0, 64.5, 222.0 ],
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 48.5, 249.0, 48.5, 249.0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 26.5, 153.0, 26.5, 153.0 ],
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 383.25, 243.0, 383.25, 243.0 ],
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 383.25, 243.0, 409.25, 243.0 ],
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 850.25, 26.5, 850.25 ],
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-48", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-50", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 880.25, 26.5, 880.25 ],
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 909.75, 26.5, 909.75 ],
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-56", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 940.25, 26.5, 940.25 ],
					"source" : [ "obj-56", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 970.0, 26.5, 970.0 ],
					"source" : [ "obj-58", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-60", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-59", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 1001.5, 26.5, 1001.5 ],
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-62", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 1031.75, 26.5, 1031.75 ],
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 1063.0, 26.5, 1063.0 ],
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-66", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 26.5, 1095.75, 26.5, 1095.75 ],
					"source" : [ "obj-67", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-69", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 274.5, 850.25, 26.5, 850.25 ],
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 383.25, 300.0, 383.25, 300.0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-70", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 274.5, 880.25, 26.5, 880.25 ],
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-73", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-72", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 274.5, 909.75, 26.5, 909.75 ],
					"source" : [ "obj-73", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-75", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-74", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 274.5, 940.25, 26.5, 940.25 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-77", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-76", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 274.5, 970.0, 26.5, 970.0 ],
					"source" : [ "obj-77", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-78", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 276.0, 1001.5, 26.5, 1001.5 ],
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-81", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-80", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 276.0, 1031.75, 26.5, 1031.75 ],
					"source" : [ "obj-81", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 276.0, 1063.0, 26.5, 1063.0 ],
					"source" : [ "obj-83", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-84", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 476.0, 850.25, 26.5, 850.25 ],
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-87", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-86", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 476.0, 882.0, 26.5, 882.0 ],
					"source" : [ "obj-87", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-89", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-88", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 476.0, 914.0, 26.5, 914.0 ],
					"source" : [ "obj-89", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 409.25, 273.0, 399.25, 273.0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-91", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"midpoints" : [ 476.0, 944.5, 26.5, 944.5 ],
					"source" : [ "obj-91", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-6" : [ "amxd~[3]", "amxd~", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "Krush_20160726.maxsnap",
				"bootpath" : "~/Documents/Max 7/Snapshots",
				"type" : "mx@s",
				"implicit" : 1
			}
 ],
		"autosave" : 0,
		"styles" : [ 			{
				"name" : "AudioStatus_Menu",
				"default" : 				{
					"bgfillcolor" : 					{
						"type" : "color",
						"color" : [ 0.294118, 0.313726, 0.337255, 1 ],
						"color1" : [ 0.454902, 0.462745, 0.482353, 0.0 ],
						"color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"angle" : 270.0,
						"proportion" : 0.39,
						"autogradient" : 0
					}

				}
,
				"parentstyle" : "",
				"multi" : 0
			}
 ]
	}

}
