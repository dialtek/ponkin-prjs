<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="8608001">
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
		<Item Name="Main.vi" Type="VI" URL="../Main.vi"/>
		<Item Name="Measure.vi" Type="VI" URL="../Measure.vi"/>
		<Item Name="Global.vi" Type="VI" URL="../Global.vi"/>
		<Item Name="GlobalInAdress.vi" Type="VI" URL="../../PSW7 30-72/GlobalInAdress.vi"/>
		<Item Name="GetVoltage.vi" Type="VI" URL="../GetVoltage.vi"/>
		<Item Name="GetCurrent.vi" Type="VI" URL="../GetCurrent.vi"/>
		<Item Name="SetVoltage.vi" Type="VI" URL="../SetVoltage.vi"/>
		<Item Name="SetCurrent.vi" Type="VI" URL="../SetCurrent.vi"/>
		<Item Name="GetOutput.vi" Type="VI" URL="../GetOutput.vi"/>
		<Item Name="SetOutput.vi" Type="VI" URL="../SetOutput.vi"/>
		<Item Name="AddChannel.vi" Type="VI" URL="../AddChannel.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Merge Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Merge Errors.vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="PSW7_30-72" Type="EXE">
				<Property Name="App_applicationGUID" Type="Str">{06A82B11-30DB-4604-9954-7A6E8385F2A9}</Property>
				<Property Name="App_applicationName" Type="Str">PSW7_30-72.exe</Property>
				<Property Name="App_fileDescription" Type="Str">PSW7_30-72</Property>
				<Property Name="App_fileVersion.major" Type="Int">1</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{290B3474-A33B-4D6E-87B7-33E0340C8133}</Property>
				<Property Name="App_INI_GUID" Type="Str">{37187E36-B73E-46A9-8D51-98A96755C8D8}</Property>
				<Property Name="App_internalName" Type="Str">PSW7_30-72</Property>
				<Property Name="App_legalCopyright" Type="Str">Copyright © 2013 </Property>
				<Property Name="App_productName" Type="Str">PSW7_30-72</Property>
				<Property Name="Bld_buildSpecName" Type="Str">PSW7_30-72</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Destination[0].destName" Type="Str">PSW7_30-72.exe</Property>
				<Property Name="Destination[0].path" Type="Path">/C/Documents and Settings/Admin/Рабочий стол/Psw distributive/internal.llb</Property>
				<Property Name="Destination[0].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">/C/Documents and Settings/Admin/Рабочий стол/Psw distributive/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{78C76E23-2D29-426D-87BD-B4F5706E7C87}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Main.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
			</Item>
			<Item Name="Install PSW" Type="Installer">
				<Property Name="AutoIncrement" Type="Bool">true</Property>
				<Property Name="BuildLabel" Type="Str">Install PSW</Property>
				<Property Name="BuildLocation" Type="Path">../../../Documents and Settings/Admin/Рабочий стол/Psw distributive/setup</Property>
				<Property Name="DirInfo.Count" Type="Int">1</Property>
				<Property Name="DirInfo.DefaultDir" Type="Str">{93760EC4-4F71-4731-9BD7-7EDE5B55E0A9}</Property>
				<Property Name="DirInfo[0].DirName" Type="Str">PSW7_30-72</Property>
				<Property Name="DirInfo[0].DirTag" Type="Str">{93760EC4-4F71-4731-9BD7-7EDE5B55E0A9}</Property>
				<Property Name="DirInfo[0].ParentTag" Type="Str">{3912416A-D2E5-411B-AFEE-B63654D690C0}</Property>
				<Property Name="DistID" Type="Str">{7B6A692F-07C4-4E03-970B-F0777426260F}</Property>
				<Property Name="DistParts.Count" Type="Int">1</Property>
				<Property Name="DistPartsInfo[0].FlavorID" Type="Str">DefaultFull</Property>
				<Property Name="DistPartsInfo[0].ProductID" Type="Str">{2CA542BC-E002-4064-84DB-49B3E558A26D}</Property>
				<Property Name="DistPartsInfo[0].ProductName" Type="Str">NI LabVIEW Run-Time Engine 8.6</Property>
				<Property Name="DistPartsInfo[0].UpgradeCode" Type="Str">{7975A1CC-5DCA-4997-EE8C-C1903BA18512}</Property>
				<Property Name="FileInfo.Count" Type="Int">3</Property>
				<Property Name="FileInfo[0].DirTag" Type="Str">{93760EC4-4F71-4731-9BD7-7EDE5B55E0A9}</Property>
				<Property Name="FileInfo[0].FileName" Type="Str">PSW7_30-72.exe</Property>
				<Property Name="FileInfo[0].FileTag" Type="Str">{06A82B11-30DB-4604-9954-7A6E8385F2A9}</Property>
				<Property Name="FileInfo[0].Type" Type="Int">3</Property>
				<Property Name="FileInfo[0].TypeID" Type="Ref">/My Computer/Build Specifications/PSW7_30-72</Property>
				<Property Name="FileInfo[1].DirTag" Type="Str">{93760EC4-4F71-4731-9BD7-7EDE5B55E0A9}</Property>
				<Property Name="FileInfo[1].FileName" Type="Str">PSW7_30-72.aliases</Property>
				<Property Name="FileInfo[1].FileTag" Type="Str">{290B3474-A33B-4D6E-87B7-33E0340C8133}</Property>
				<Property Name="FileInfo[1].Type" Type="Int">3</Property>
				<Property Name="FileInfo[1].TypeID" Type="Ref">/My Computer/Build Specifications/PSW7_30-72</Property>
				<Property Name="FileInfo[2].DirTag" Type="Str">{93760EC4-4F71-4731-9BD7-7EDE5B55E0A9}</Property>
				<Property Name="FileInfo[2].FileName" Type="Str">PSW7_30-72.ini</Property>
				<Property Name="FileInfo[2].FileTag" Type="Str">{37187E36-B73E-46A9-8D51-98A96755C8D8}</Property>
				<Property Name="FileInfo[2].Type" Type="Int">3</Property>
				<Property Name="FileInfo[2].TypeID" Type="Ref">/My Computer/Build Specifications/PSW7_30-72</Property>
				<Property Name="InstSpecVersion" Type="Str">8608001</Property>
				<Property Name="LicenseFile" Type="Ref"></Property>
				<Property Name="OSCheck" Type="Int">0</Property>
				<Property Name="OSCheck_Vista" Type="Bool">false</Property>
				<Property Name="ProductName" Type="Str">PSW7_30-72</Property>
				<Property Name="ProductVersion" Type="Str">1.0.1</Property>
				<Property Name="ReadmeFile" Type="Ref"></Property>
				<Property Name="ShortcutInfo.Count" Type="Int">1</Property>
				<Property Name="ShortcutInfo[0].DirTag" Type="Str">{B9E310F1-839C-48B7-8CAE-33000780C26E}</Property>
				<Property Name="ShortcutInfo[0].FileTag" Type="Str">{06A82B11-30DB-4604-9954-7A6E8385F2A9}</Property>
				<Property Name="ShortcutInfo[0].FileTagDir" Type="Str">{93760EC4-4F71-4731-9BD7-7EDE5B55E0A9}</Property>
				<Property Name="ShortcutInfo[0].Name" Type="Str">PSW7_30-72</Property>
				<Property Name="ShortcutInfo[0].SubDir" Type="Str">PSW7_30-72</Property>
				<Property Name="UpgradeCode" Type="Str">{E88B7A64-FE75-480A-8EE5-C5E17B269D09}</Property>
			</Item>
		</Item>
	</Item>
</Project>
