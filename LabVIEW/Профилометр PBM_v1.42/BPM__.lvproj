<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="15008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="BPM_main__.vi" Type="VI" URL="../BPM_main__.vi"/>
		<Item Name="Cluster_to_string_(SubVI).vi" Type="VI" URL="../Cluster_to_string_(SubVI).vi"/>
		<Item Name="Concatinate MODBUS regs (SubVI).vi" Type="VI" URL="../Concatinate MODBUS regs (SubVI).vi"/>
		<Item Name="Create RTU Over TCP Master.vi" Type="VI" URL="../Create RTU Over TCP Master.vi"/>
		<Item Name="Create_and_save_to_file (SubVI).vi" Type="VI" URL="../Create_and_save_to_file (SubVI).vi"/>
		<Item Name="Get path from coef.file (SubVI).vi" Type="VI" URL="../Get path from coef.file (SubVI).vi"/>
		<Item Name="Read and Write Controls to Automatic Config File.vi" Type="VI" URL="../Load and Save Controls_LV2009.llb/Read and Write Controls to Automatic Config File.vi"/>
		<Item Name="String_to_num (SubVI).vi" Type="VI" URL="../String_to_num (SubVI).vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="8.6CompatibleGlobalVar.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/config.llb/8.6CompatibleGlobalVar.vi"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="Bits to Bytes.vi" Type="VI" URL="/&lt;vilib&gt;/NI/Modbus Library/Utility/Bits to Bytes.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Bytes to Bits.vi" Type="VI" URL="/&lt;vilib&gt;/NI/Modbus Library/Utility/Bytes to Bits.vi"/>
				<Item Name="Bytes to U16s.vi" Type="VI" URL="/&lt;vilib&gt;/NI/Modbus Library/Utility/Bytes to U16s.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="Device Data Model.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Data Model/Device Data Model.lvclass"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Generate UUID.vi" Type="VI" URL="/&lt;vilib&gt;/NI/Modbus Library/Utility/Generate UUID.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="Master Function Definition.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Master Function Definition/Master Function Definition.lvclass"/>
				<Item Name="Modbus API.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/API/Modbus API.lvclass"/>
				<Item Name="Modbus Data Unit.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Modbus Data Unit/Modbus Data Unit.lvclass"/>
				<Item Name="Modbus Master.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/API/Master/Modbus Master.lvclass"/>
				<Item Name="Network Master.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Network Protocol/Network Master/Network Master.lvclass"/>
				<Item Name="Network Protocol.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Network Protocol/Network Protocol.lvclass"/>
				<Item Name="Network Slave.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Network Protocol/Network Slave/Network Slave.lvclass"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="RTU Data Unit.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Transmission Data Unit/RTU/RTU Data Unit.lvclass"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Serial Data Unit.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Transmission Data Unit/Serial Interface/Serial Data Unit.lvclass"/>
				<Item Name="Serial Master.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Network Protocol/Network Master/Serial/Serial Master.lvclass"/>
				<Item Name="Serial Shared Components.lvlib" Type="Library" URL="/&lt;vilib&gt;/NI/Modbus Library/Serial Shared Components/Serial Shared Components.lvlib"/>
				<Item Name="Serial Slave.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Network Protocol/Network Slave/Serial/Serial Slave.lvclass"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="TCP Master.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Network Protocol/Network Master/TCP/TCP Master.lvclass"/>
				<Item Name="TCP Shared Components.lvlib" Type="Library" URL="/&lt;vilib&gt;/NI/Modbus Library/TCP Shared Components/TCP Shared Components.lvlib"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Transmission Data Unit.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/NI/Modbus Library/Transmission Data Unit/Transmission Data Unit.lvclass"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="U16s to Bytes.vi" Type="VI" URL="/&lt;vilib&gt;/NI/Modbus Library/Utility/U16s to Bytes.vi"/>
				<Item Name="VISA Flush IO Buffer Mask.ctl" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Flush IO Buffer Mask.ctl"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="Read and Write Controls to Config File.vi" Type="VI" URL="../Load and Save Controls_LV2009.llb/Read and Write Controls to Config File.vi"/>
			<Item Name="RWC_Actions.ctl" Type="VI" URL="../Load and Save Controls_LV2009.llb/RWC_Actions.ctl"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="BPM Installer" Type="Installer">
				<Property Name="Destination[0].name" Type="Str">BPM__</Property>
				<Property Name="Destination[0].parent" Type="Str">{3912416A-D2E5-411B-AFEE-B63654D690C0}</Property>
				<Property Name="Destination[0].tag" Type="Str">{E707489C-5CC7-44C0-A870-494FC84F8D88}</Property>
				<Property Name="Destination[0].type" Type="Str">userFolder</Property>
				<Property Name="DestinationCount" Type="Int">1</Property>
				<Property Name="DistPart[0].flavorID" Type="Str">DefaultFull</Property>
				<Property Name="DistPart[0].productID" Type="Str">{1CB9B79D-FBCA-43F4-B990-65BD2145BDD0}</Property>
				<Property Name="DistPart[0].productName" Type="Str">NI LabVIEW Runtime 2015</Property>
				<Property Name="DistPart[0].SoftDep[0].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[0].productName" Type="Str">NI LabVIEW Runtime 2015 Non-English Support.</Property>
				<Property Name="DistPart[0].SoftDep[0].upgradeCode" Type="Str">{128ABF1E-5F69-40D1-8A81-33DCF8229F08}</Property>
				<Property Name="DistPart[0].SoftDep[1].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[1].productName" Type="Str">NI ActiveX Container</Property>
				<Property Name="DistPart[0].SoftDep[1].upgradeCode" Type="Str">{1038A887-23E1-4289-B0BD-0C4B83C6BA21}</Property>
				<Property Name="DistPart[0].SoftDep[10].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[10].productName" Type="Str">NI mDNS Responder 14.0</Property>
				<Property Name="DistPart[0].SoftDep[10].upgradeCode" Type="Str">{9607874B-4BB3-42CB-B450-A2F5EF60BA3B}</Property>
				<Property Name="DistPart[0].SoftDep[11].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[11].productName" Type="Str">NI Deployment Framework 2015</Property>
				<Property Name="DistPart[0].SoftDep[11].upgradeCode" Type="Str">{838942E4-B73C-492E-81A3-AA1E291FD0DC}</Property>
				<Property Name="DistPart[0].SoftDep[12].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[12].productName" Type="Str">NI Error Reporting 2015</Property>
				<Property Name="DistPart[0].SoftDep[12].upgradeCode" Type="Str">{42E818C6-2B08-4DE7-BD91-B0FD704C119A}</Property>
				<Property Name="DistPart[0].SoftDep[2].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[2].productName" Type="Str">NI System Web Server 15.0</Property>
				<Property Name="DistPart[0].SoftDep[2].upgradeCode" Type="Str">{FCF64B73-B7D4-4971-8F11-24BAF7CC3E6C}</Property>
				<Property Name="DistPart[0].SoftDep[3].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[3].productName" Type="Str">Math Kernel Libraries</Property>
				<Property Name="DistPart[0].SoftDep[3].upgradeCode" Type="Str">{4C0854AD-9BFC-4494-A4E0-D96C0C07F1F2}</Property>
				<Property Name="DistPart[0].SoftDep[4].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[4].productName" Type="Str">NI Logos 15.0</Property>
				<Property Name="DistPart[0].SoftDep[4].upgradeCode" Type="Str">{5E4A4CE3-4D06-11D4-8B22-006008C16337}</Property>
				<Property Name="DistPart[0].SoftDep[5].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[5].productName" Type="Str">NI TDM Streaming 15.0</Property>
				<Property Name="DistPart[0].SoftDep[5].upgradeCode" Type="Str">{4CD11BE6-6BB7-4082-8A27-C13771BC309B}</Property>
				<Property Name="DistPart[0].SoftDep[6].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[6].productName" Type="Str">NI LabVIEW Web Server 2015</Property>
				<Property Name="DistPart[0].SoftDep[6].upgradeCode" Type="Str">{78AAB900-C712-11E3-9C1A-0800200C9A66}</Property>
				<Property Name="DistPart[0].SoftDep[7].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[7].productName" Type="Str">NI LabVIEW Real-Time NBFifo 2015</Property>
				<Property Name="DistPart[0].SoftDep[7].upgradeCode" Type="Str">{25643B9A-90E8-4100-B30C-10EC4DE2EE68}</Property>
				<Property Name="DistPart[0].SoftDep[8].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[8].productName" Type="Str">NI VC2008MSMs</Property>
				<Property Name="DistPart[0].SoftDep[8].upgradeCode" Type="Str">{FDA3F8BB-BAA9-45D7-8DC7-22E1F5C76315}</Property>
				<Property Name="DistPart[0].SoftDep[9].exclude" Type="Bool">false</Property>
				<Property Name="DistPart[0].SoftDep[9].productName" Type="Str">NI VC2010MSMs</Property>
				<Property Name="DistPart[0].SoftDep[9].upgradeCode" Type="Str">{EFBA6F9E-F934-4BD7-AC51-60CCA480489C}</Property>
				<Property Name="DistPart[0].SoftDepCount" Type="Int">13</Property>
				<Property Name="DistPart[0].upgradeCode" Type="Str">{CA8FF739-2EDA-4134-9A70-0F5DD933FDED}</Property>
				<Property Name="DistPartCount" Type="Int">1</Property>
				<Property Name="INST_autoIncrement" Type="Bool">true</Property>
				<Property Name="INST_buildLocation" Type="Path">../Профилометр PBM_v1.42/installer/BPM_.lvlps</Property>
				<Property Name="INST_buildLocation.type" Type="Str">relativeToCommon</Property>
				<Property Name="INST_buildSpecName" Type="Str">BPM Installer</Property>
				<Property Name="INST_defaultDir" Type="Str">{E707489C-5CC7-44C0-A870-494FC84F8D88}</Property>
				<Property Name="INST_productName" Type="Str">BPM_</Property>
				<Property Name="INST_productVersion" Type="Str">1.0.1</Property>
				<Property Name="InstSpecBitness" Type="Str">32-bit</Property>
				<Property Name="InstSpecVersion" Type="Str">15008024</Property>
				<Property Name="MSI_autoselectDrivers" Type="Bool">true</Property>
				<Property Name="MSI_distID" Type="Str">{51F53CC4-7C8C-4459-AE0B-50E8DDBF1A68}</Property>
				<Property Name="MSI_hideNonRuntimes" Type="Bool">true</Property>
				<Property Name="MSI_osCheck" Type="Int">0</Property>
				<Property Name="MSI_upgradeCode" Type="Str">{8220C985-BF6F-4DC5-A07F-6F9BC31B0060}</Property>
				<Property Name="RegDest[0].dirName" Type="Str">Software</Property>
				<Property Name="RegDest[0].dirTag" Type="Str">{DDFAFC8B-E728-4AC8-96DE-B920EBB97A86}</Property>
				<Property Name="RegDest[0].parentTag" Type="Str">2</Property>
				<Property Name="RegDestCount" Type="Int">1</Property>
				<Property Name="Source[0].dest" Type="Str">{E707489C-5CC7-44C0-A870-494FC84F8D88}</Property>
				<Property Name="Source[0].File[0].dest" Type="Str">{E707489C-5CC7-44C0-A870-494FC84F8D88}</Property>
				<Property Name="Source[0].File[0].name" Type="Str">BPM v1.42.exe</Property>
				<Property Name="Source[0].File[0].Shortcut[0].destIndex" Type="Int">0</Property>
				<Property Name="Source[0].File[0].Shortcut[0].name" Type="Str">BPM v1.42</Property>
				<Property Name="Source[0].File[0].Shortcut[0].subDir" Type="Str">BPM__</Property>
				<Property Name="Source[0].File[0].ShortcutCount" Type="Int">1</Property>
				<Property Name="Source[0].File[0].tag" Type="Str">{3AA49B60-EFD1-4CBE-B30D-C7227C4F710A}</Property>
				<Property Name="Source[0].FileCount" Type="Int">1</Property>
				<Property Name="Source[0].name" Type="Str">Профилометр BPM v1.42</Property>
				<Property Name="Source[0].tag" Type="Ref">/My Computer/Build Specifications/Профилометр BPM v1.42</Property>
				<Property Name="Source[0].type" Type="Str">EXE</Property>
				<Property Name="SourceCount" Type="Int">1</Property>
			</Item>
			<Item Name="Профилометр BPM v1.42" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{E63E86DC-58D4-4BE8-A0ED-F496B35944CA}</Property>
				<Property Name="App_INI_GUID" Type="Str">{62CF3540-26CA-4126-A8A0-DA19552A63DB}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{3EB70610-259F-44C1-BF72-5615402F1725}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Профилометр BPM v1.42</Property>
				<Property Name="Bld_compilerOptLevel" Type="Int">0</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../EXE</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{47A5E0D8-3491-47FF-B207-54885F2B94B1}</Property>
				<Property Name="Bld_supportedLanguage[0]" Type="Str">English</Property>
				<Property Name="Bld_supportedLanguageCount" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">BPM v1.42.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../EXE/BPM v1.42.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../EXE/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_actXinfo_enumCLSID[0]" Type="Str">{0EBB797A-D012-4034-8813-C736AE559220}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[1]" Type="Str">{EE1E64B4-C6AB-481C-8069-6FD1EE9F2430}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[10]" Type="Str">{CE6046D0-90E8-4843-B226-CE3FEEFE29DB}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[11]" Type="Str">{6A74B10D-1D6F-4D67-8615-16B8A47F596A}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[12]" Type="Str">{FD08BEFC-93DB-4946-BA82-35DE9F6A0734}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[13]" Type="Str">{6CED31AF-0E94-4BF2-88B6-3337F6CB9AE3}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[14]" Type="Str">{09817194-2780-4A73-B71F-D06846F10176}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[15]" Type="Str">{8B3FDDDC-C6F7-43FB-9F17-0B50E8C88EB6}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[16]" Type="Str">{8A986729-88E1-4C2B-BB18-BA74847EE624}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[2]" Type="Str">{21DF1558-FDCE-4678-AEE3-C98F5AABC904}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[3]" Type="Str">{64EC29A2-D69A-441B-8E42-6134E3C454B4}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[4]" Type="Str">{D633DC26-54D5-454F-98F7-DDF0709A8370}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[5]" Type="Str">{02FBB760-59F5-4617-A9AC-CA8BD4FCA3C5}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[6]" Type="Str">{36A02F80-9600-49A1-A4CD-E8F5721F8AC0}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[7]" Type="Str">{75268E2E-2E24-4F65-9B80-71D9144CDDDF}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[8]" Type="Str">{CD92EDB8-2450-401B-BF4E-81FB1920F6BA}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[9]" Type="Str">{23A24C01-A2A7-49FE-B020-D3900783AB85}</Property>
				<Property Name="Exe_actXinfo_enumCLSIDsCount" Type="Int">17</Property>
				<Property Name="Exe_actXinfo_majorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_minorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_objCLSID[0]" Type="Str">{14D27E4C-7879-4676-B5DE-D87443630250}</Property>
				<Property Name="Exe_actXinfo_objCLSID[1]" Type="Str">{51644976-2C3E-4E78-89EF-247F24788079}</Property>
				<Property Name="Exe_actXinfo_objCLSID[10]" Type="Str">{5E300887-4E69-4466-B534-E0FBF4FA057B}</Property>
				<Property Name="Exe_actXinfo_objCLSID[11]" Type="Str">{8DC7C7B6-6570-42E8-96E8-0ADC7E67856E}</Property>
				<Property Name="Exe_actXinfo_objCLSID[12]" Type="Str">{389A33C4-5ECC-485E-B71A-21887235337E}</Property>
				<Property Name="Exe_actXinfo_objCLSID[13]" Type="Str">{70738AC0-4481-43A5-B80B-D4AD098B36ED}</Property>
				<Property Name="Exe_actXinfo_objCLSID[2]" Type="Str">{EF1E30FC-C731-4315-82E4-29AE781F6268}</Property>
				<Property Name="Exe_actXinfo_objCLSID[3]" Type="Str">{14B2F60F-B34E-4FA0-AF88-6F84A7C779FA}</Property>
				<Property Name="Exe_actXinfo_objCLSID[4]" Type="Str">{EACA53AB-82E8-413F-80BA-D25AF565DBF6}</Property>
				<Property Name="Exe_actXinfo_objCLSID[5]" Type="Str">{807F6A2B-7F06-45AF-8B5A-A90F1E47B0EE}</Property>
				<Property Name="Exe_actXinfo_objCLSID[6]" Type="Str">{E574C8C5-D657-4DB9-911F-2778929EEF57}</Property>
				<Property Name="Exe_actXinfo_objCLSID[7]" Type="Str">{4DB90243-84C3-4128-BE61-AAB582BDC340}</Property>
				<Property Name="Exe_actXinfo_objCLSID[8]" Type="Str">{5D568682-56E4-4A75-957D-B37CEB590B93}</Property>
				<Property Name="Exe_actXinfo_objCLSID[9]" Type="Str">{37684287-C091-4B13-B657-0BFDAA1E86CE}</Property>
				<Property Name="Exe_actXinfo_objCLSIDsCount" Type="Int">14</Property>
				<Property Name="Exe_actXinfo_progIDPrefix" Type="Str">BPMV142</Property>
				<Property Name="Exe_actXServerName" Type="Str">BPMV142</Property>
				<Property Name="Exe_actXServerNameGUID" Type="Str">{17C8CFCB-EB9C-47F0-AE06-2198A2596868}</Property>
				<Property Name="Source[0].itemID" Type="Str">{4EF37CC6-AFD8-4D7B-8671-14692C147BEC}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/BPM_main__.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Cluster_to_string_(SubVI).vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/Concatinate MODBUS regs (SubVI).vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/Create RTU Over TCP Master.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/Create_and_save_to_file (SubVI).vi</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/Get path from coef.file (SubVI).vi</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/My Computer/String_to_num (SubVI).vi</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">VI</Property>
				<Property Name="Source[8].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[8].itemID" Type="Ref">/My Computer/Read and Write Controls to Automatic Config File.vi</Property>
				<Property Name="Source[8].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[8].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">9</Property>
				<Property Name="TgtF_productName" Type="Str">Профилометр BPM v1.42</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{3AA49B60-EFD1-4CBE-B30D-C7227C4F710A}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">BPM v1.42.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
