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
				<Property Name="Bld_version.build" Type="Int">13</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">HILAC LEBT correctors.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../exe/HILAC LEBT correctors.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../exe/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_actXinfo_enumCLSID[0]" Type="Str">{46170092-D4CE-44BB-AF43-F4482AD4BBD5}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[1]" Type="Str">{E25796FC-03A8-4FC7-8C83-CD048D411D3C}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[10]" Type="Str">{D2E19826-5D14-41EE-8880-2D179A66EC30}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[11]" Type="Str">{9550F2AE-72C1-4D3F-B213-7AE067E5442D}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[12]" Type="Str">{863942AF-EE39-4C68-A26B-6653528F6BE6}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[13]" Type="Str">{19242F00-4D69-491B-A780-B9519ADA7DF9}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[14]" Type="Str">{9B2D7276-1A1F-4FC0-9624-3ADC3A5236BC}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[15]" Type="Str">{AF707FBA-EC9C-4536-A594-D7B2AEE4DE3A}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[16]" Type="Str">{1829C528-13CC-451A-B400-B4695A65A582}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[2]" Type="Str">{9C112022-04D4-4659-9352-7C7FE7EEE191}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[3]" Type="Str">{060A0967-9DE0-4B0B-AEE2-5AF8DF4BBA28}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[4]" Type="Str">{F4AEF6E3-1F38-4FF7-B1B6-238AC42E64FB}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[5]" Type="Str">{49D3642F-4774-406B-A52E-4604DEA82804}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[6]" Type="Str">{0E191372-59D6-4B48-A0B7-C803E2077B79}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[7]" Type="Str">{A8B7336C-6EA9-4632-9B8B-8B61AE5429A4}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[8]" Type="Str">{F353FC03-682F-4A00-B25A-64306B1C8BF9}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[9]" Type="Str">{55089DFB-FB6C-4A18-86B4-50B2623BD2E9}</Property>
				<Property Name="Exe_actXinfo_enumCLSIDsCount" Type="Int">17</Property>
				<Property Name="Exe_actXinfo_majorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_minorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_objCLSID[0]" Type="Str">{420D3C73-E4F1-461B-B8C4-A7EC61F2F3E7}</Property>
				<Property Name="Exe_actXinfo_objCLSID[1]" Type="Str">{09928735-C3F5-4565-BD76-788B16BBEF5F}</Property>
				<Property Name="Exe_actXinfo_objCLSID[10]" Type="Str">{C756A719-BDB1-431F-86DD-C66734CFCE32}</Property>
				<Property Name="Exe_actXinfo_objCLSID[11]" Type="Str">{0088C630-2B5C-4D79-89B7-5043CD07C0C0}</Property>
				<Property Name="Exe_actXinfo_objCLSID[12]" Type="Str">{C11CA638-CCE1-4CB1-A8F0-836D7515828D}</Property>
				<Property Name="Exe_actXinfo_objCLSID[13]" Type="Str">{39474DD5-4713-46E2-BBCB-A81A03ACF5A0}</Property>
				<Property Name="Exe_actXinfo_objCLSID[2]" Type="Str">{D6AC4283-C247-44E6-A0AB-A6D0364EA3AA}</Property>
				<Property Name="Exe_actXinfo_objCLSID[3]" Type="Str">{EA8238F4-D9A9-442A-B81B-37A4154A2465}</Property>
				<Property Name="Exe_actXinfo_objCLSID[4]" Type="Str">{FB005348-54B7-4C40-BF9A-20FB3C139C60}</Property>
				<Property Name="Exe_actXinfo_objCLSID[5]" Type="Str">{C4557300-7655-4370-A01B-FF4FAA0DD43E}</Property>
				<Property Name="Exe_actXinfo_objCLSID[6]" Type="Str">{9A9CCFB1-293A-4D00-BCBD-505223EA5D06}</Property>
				<Property Name="Exe_actXinfo_objCLSID[7]" Type="Str">{AD2356AA-5D81-4D3A-954B-205A7CA6C508}</Property>
				<Property Name="Exe_actXinfo_objCLSID[8]" Type="Str">{15A973B3-100A-4455-9AE5-F1530C113FA8}</Property>
				<Property Name="Exe_actXinfo_objCLSID[9]" Type="Str">{B050E7FB-D7EA-4043-8D1D-BFF43640775A}</Property>
				<Property Name="Exe_actXinfo_objCLSIDsCount" Type="Int">14</Property>
				<Property Name="Exe_actXinfo_progIDPrefix" Type="Str">HILACLEBTCorrectors</Property>
				<Property Name="Exe_actXServerName" Type="Str">HILACLEBTCorrectors</Property>
				<Property Name="Exe_actXServerNameGUID" Type="Str"></Property>
				<Property Name="Source[0].itemID" Type="Str">{17BAD2F7-F330-42C4-B909-54D83E81FD21}</Property>
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
				<Property Name="TgtF_targetfileName" Type="Str">HILAC LEBT correctors.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
