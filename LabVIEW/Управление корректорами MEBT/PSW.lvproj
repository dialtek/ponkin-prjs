<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Main.vi" Type="VI" URL="../Main.vi"/>
		<Item Name="GetCurrent.vi" Type="VI" URL="../GetCurrent.vi"/>
		<Item Name="GetVoltage.vi" Type="VI" URL="../GetVoltage.vi"/>
		<Item Name="SetVoltage.vi" Type="VI" URL="../SetVoltage.vi"/>
		<Item Name="SetCurrent.vi" Type="VI" URL="../SetCurrent.vi"/>
		<Item Name="SetOutput.vi" Type="VI" URL="../SetOutput.vi"/>
		<Item Name="GetOutState_ins.vi" Type="VI" URL="../../He Src Bevatech/GetOutState_ins.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="General Error Handler CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler CORE.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="pgm" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{6069CEB9-39C4-4C38-9E76-23361F89A64F}</Property>
				<Property Name="App_INI_GUID" Type="Str">{00E6CC1B-606F-438E-88BE-1CC94B6F2932}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{564C8AC9-3813-41B7-AB28-23E0AEBACA0D}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">pgm</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../exe</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{14D82D85-8880-4C97-9177-37085E2673C3}</Property>
				<Property Name="Bld_version.build" Type="Int">14</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">HILAC MEBT correctors.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../exe/HILAC MEBT correctors.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../exe/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_actXinfo_enumCLSID[0]" Type="Str">{1CD4F298-4BAF-42CE-B80F-AE262EFDA3B5}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[1]" Type="Str">{B93179AE-C7BA-4E7A-BD3E-39EE4324A1ED}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[10]" Type="Str">{43D23D46-FE79-4FF4-AD3D-AC773BFB2883}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[11]" Type="Str">{EA4317BE-5A7D-4558-AA13-3828140E832A}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[12]" Type="Str">{75AE78A5-F0E3-4C70-88B3-ABFF7A819228}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[13]" Type="Str">{2941CBD6-0609-40F8-A133-5E79294F17EF}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[14]" Type="Str">{FA76CBB6-A292-4789-9610-6DE06157B9B1}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[15]" Type="Str">{DC83C209-3434-4075-8DF3-1EED4A6372BA}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[16]" Type="Str">{D4F0EEB2-D2B8-4F32-A31B-AB6268FE0B2A}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[2]" Type="Str">{C78D86D5-6A8F-460C-BD37-002F324F8FEC}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[3]" Type="Str">{EDF0ABC7-D5A4-45EA-9158-95A6D6E8040C}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[4]" Type="Str">{115A2D75-D934-4A45-9BBB-E064BCA54C3B}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[5]" Type="Str">{0ADEF896-0A5D-4889-AD5C-D1FBAD585796}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[6]" Type="Str">{827EDAD9-E135-4CA7-882E-29253F3B6AD1}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[7]" Type="Str">{C0F4034B-79AE-4253-AB34-AA12271CB25B}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[8]" Type="Str">{4F2FDD0B-92B7-4485-9524-686C186CF090}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[9]" Type="Str">{45895EA2-C4DC-442D-AB8A-B9B32985775C}</Property>
				<Property Name="Exe_actXinfo_enumCLSIDsCount" Type="Int">17</Property>
				<Property Name="Exe_actXinfo_majorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_minorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_objCLSID[0]" Type="Str">{C84EF282-2562-4A8E-A4D7-E816E0D1052F}</Property>
				<Property Name="Exe_actXinfo_objCLSID[1]" Type="Str">{4D804D7D-8BB4-499E-859D-6AC55592A099}</Property>
				<Property Name="Exe_actXinfo_objCLSID[10]" Type="Str">{FEA98BF5-D672-40D7-881B-F3B6997BEFB5}</Property>
				<Property Name="Exe_actXinfo_objCLSID[11]" Type="Str">{FF66C2D8-86C8-4874-846D-44B78CB5E804}</Property>
				<Property Name="Exe_actXinfo_objCLSID[12]" Type="Str">{ED1E8D3F-E2BB-49D0-B61A-1F8888F05EC0}</Property>
				<Property Name="Exe_actXinfo_objCLSID[13]" Type="Str">{4EE0503B-F3B0-40AB-84FD-013EE1A22E32}</Property>
				<Property Name="Exe_actXinfo_objCLSID[2]" Type="Str">{21DB2D3A-7E87-4049-A29F-08EFA14E78F6}</Property>
				<Property Name="Exe_actXinfo_objCLSID[3]" Type="Str">{1BC3B6FE-03E0-4D16-9C74-D9E7FF6F5B67}</Property>
				<Property Name="Exe_actXinfo_objCLSID[4]" Type="Str">{3113AF25-FE27-474C-9E1A-4DFCA67006E3}</Property>
				<Property Name="Exe_actXinfo_objCLSID[5]" Type="Str">{06849AF3-AF76-4284-97AD-9CA6BE3618E2}</Property>
				<Property Name="Exe_actXinfo_objCLSID[6]" Type="Str">{0FF9064B-EF5D-4B9A-BC48-FA6D80B4E2CE}</Property>
				<Property Name="Exe_actXinfo_objCLSID[7]" Type="Str">{02BBD109-9E90-416A-8E46-0BE84EA4F830}</Property>
				<Property Name="Exe_actXinfo_objCLSID[8]" Type="Str">{C945319D-2715-410F-AEF5-B31BA71DEBA2}</Property>
				<Property Name="Exe_actXinfo_objCLSID[9]" Type="Str">{BDF9AC91-79B5-4BB1-A4EC-A4B4A1D019E9}</Property>
				<Property Name="Exe_actXinfo_objCLSIDsCount" Type="Int">14</Property>
				<Property Name="Exe_actXinfo_progIDPrefix" Type="Str">HILACMEBTCorrectors</Property>
				<Property Name="Exe_actXServerName" Type="Str">HILACMEBTCorrectors</Property>
				<Property Name="Exe_actXServerNameGUID" Type="Str"></Property>
				<Property Name="Source[0].itemID" Type="Str">{59B6F1A1-9B82-4E11-8B7D-331B9C09D50B}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Main.vi</Property>
				<Property Name="Source[1].properties[0].type" Type="Str">Window has title bar</Property>
				<Property Name="Source[1].properties[0].value" Type="Bool">true</Property>
				<Property Name="Source[1].properties[1].type" Type="Str">Show menu bar</Property>
				<Property Name="Source[1].properties[1].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[2].type" Type="Str">Show vertical scroll bar</Property>
				<Property Name="Source[1].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[3].type" Type="Str">Show horizontal scroll bar</Property>
				<Property Name="Source[1].properties[3].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[4].type" Type="Str">Show toolbar</Property>
				<Property Name="Source[1].properties[4].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[5].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[1].properties[5].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[6].type" Type="Str">Window behavior</Property>
				<Property Name="Source[1].properties[6].value" Type="Str">Default</Property>
				<Property Name="Source[1].properties[7].type" Type="Str">Allow user to close window</Property>
				<Property Name="Source[1].properties[7].value" Type="Bool">true</Property>
				<Property Name="Source[1].propertiesCount" Type="Int">8</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/GetCurrent.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/GetVoltage.vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/SetVoltage.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/SetCurrent.vi</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/SetOutput.vi</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">7</Property>
				<Property Name="TgtF_fileDescription" Type="Str">pgm</Property>
				<Property Name="TgtF_internalName" Type="Str">pgm</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2015 </Property>
				<Property Name="TgtF_productName" Type="Str">pgm</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{DDE6CB7C-5D28-4CD2-AC5F-A81BF9F732F6}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">HILAC MEBT correctors.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
