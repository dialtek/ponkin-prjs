<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_20(15:0)" />
        <signal name="XLXN_21" />
        <signal name="XLXN_23" />
        <signal name="XLXN_26" />
        <signal name="XLXN_28" />
        <signal name="XLXN_30" />
        <blockdef name="sr16ce">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="64" x="320" y="-268" height="24" />
            <rect width="256" x="64" y="-384" height="320" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
        </blockdef>
        <blockdef name="sr4cle">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-768" height="704" />
            <line x2="64" y1="-704" y2="-704" x1="0" />
            <line x2="64" y1="-640" y2="-640" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="320" y1="-640" y2="-640" x1="384" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
        </blockdef>
        <blockdef name="sr16cle">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="64" x="320" y="-396" height="24" />
            <rect width="64" x="0" y="-524" height="24" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <rect width="256" x="64" y="-640" height="576" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-96" x1="64" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="64" y1="-64" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="96" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="64" />
        </blockdef>
        <block symbolname="sr16ce" name="XLXI_31">
            <blockpin name="C" />
            <blockpin name="CE" />
            <blockpin name="CLR" />
            <blockpin name="SLI" />
            <blockpin signalname="XLXN_20(15:0)" name="Q(15:0)" />
        </block>
        <block symbolname="sr16cle" name="XLXI_36">
            <blockpin name="C" />
            <blockpin signalname="XLXN_26" name="CE" />
            <blockpin name="CLR" />
            <blockpin signalname="XLXN_20(15:0)" name="D(15:0)" />
            <blockpin signalname="XLXN_23" name="L" />
            <blockpin signalname="XLXN_21" name="SLI" />
            <blockpin name="Q(15:0)" />
        </block>
        <block symbolname="sr4cle" name="XLXI_39">
            <blockpin name="C" />
            <blockpin signalname="XLXN_26" name="CE" />
            <blockpin name="CLR" />
            <blockpin signalname="XLXN_28" name="D0" />
            <blockpin signalname="XLXN_30" name="D1" />
            <blockpin signalname="XLXN_28" name="D2" />
            <blockpin signalname="XLXN_30" name="D3" />
            <blockpin signalname="XLXN_23" name="L" />
            <blockpin signalname="XLXN_30" name="SLI" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin signalname="XLXN_21" name="Q3" />
        </block>
        <block symbolname="gnd" name="XLXI_37">
            <blockpin signalname="XLXN_30" name="G" />
        </block>
        <block symbolname="vcc" name="XLXI_38">
            <blockpin signalname="XLXN_28" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1616" y="512" name="XLXI_31" orien="R0" />
        <instance x="2352" y="768" name="XLXI_36" orien="R0" />
        <branch name="XLXN_20(15:0)">
            <wire x2="2352" y1="256" y2="256" x1="2000" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="2080" y1="1072" y2="1072" x1="2016" />
            <wire x2="2080" y1="192" y2="1072" x1="2080" />
            <wire x2="2352" y1="192" y2="192" x1="2080" />
        </branch>
        <instance x="1632" y="1520" name="XLXI_39" orien="R0" />
        <branch name="XLXN_23">
            <wire x2="1408" y1="528" y2="1200" x1="1408" />
            <wire x2="1632" y1="1200" y2="1200" x1="1408" />
            <wire x2="2352" y1="528" y2="528" x1="1408" />
            <wire x2="2352" y1="448" y2="528" x1="2352" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="1632" y1="1328" y2="1328" x1="1408" />
            <wire x2="1408" y1="1328" y2="1696" x1="1408" />
            <wire x2="2272" y1="1696" y2="1696" x1="1408" />
            <wire x2="2352" y1="576" y2="576" x1="2272" />
            <wire x2="2272" y1="576" y2="1696" x1="2272" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="1504" y1="864" y2="880" x1="1504" />
            <wire x2="1504" y1="880" y2="1008" x1="1504" />
            <wire x2="1632" y1="1008" y2="1008" x1="1504" />
            <wire x2="1632" y1="880" y2="880" x1="1504" />
        </branch>
        <instance x="1440" y="864" name="XLXI_38" orien="R0" />
        <branch name="XLXN_30">
            <wire x2="1632" y1="816" y2="816" x1="1552" />
            <wire x2="1552" y1="816" y2="944" x1="1552" />
            <wire x2="1632" y1="944" y2="944" x1="1552" />
            <wire x2="1552" y1="944" y2="1072" x1="1552" />
            <wire x2="1632" y1="1072" y2="1072" x1="1552" />
            <wire x2="1552" y1="1072" y2="1104" x1="1552" />
        </branch>
        <instance x="1488" y="1232" name="XLXI_37" orien="R0" />
    </sheet>
</drawing>