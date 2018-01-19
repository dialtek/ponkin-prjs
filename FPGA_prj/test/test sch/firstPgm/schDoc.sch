<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="SW1" />
        <signal name="clock" />
        <signal name="LED1" />
        <signal name="SW3" />
        <signal name="LED3" />
        <signal name="SW2" />
        <signal name="LED2" />
        <signal name="LED4" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="SW4" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <port polarity="Input" name="SW1" />
        <port polarity="Input" name="clock" />
        <port polarity="Output" name="LED1" />
        <port polarity="Input" name="SW3" />
        <port polarity="Output" name="LED3" />
        <port polarity="Input" name="SW2" />
        <port polarity="Output" name="LED2" />
        <port polarity="Output" name="LED4" />
        <port polarity="Input" name="SW4" />
        <blockdef name="ifd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="64" y1="-128" y2="-140" x1="84" />
            <line x2="84" y1="-116" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
        </blockdef>
        <block symbolname="ifd" name="XLXI_1">
            <blockpin signalname="clock" name="C" />
            <blockpin signalname="SW1" name="D" />
            <blockpin signalname="LED1" name="Q" />
        </block>
        <block symbolname="ifd" name="XLXI_3">
            <blockpin signalname="clock" name="C" />
            <blockpin signalname="SW2" name="D" />
            <blockpin signalname="LED2" name="Q" />
        </block>
        <block symbolname="ifd" name="XLXI_4">
            <blockpin signalname="clock" name="C" />
            <blockpin signalname="SW3" name="D" />
            <blockpin signalname="LED3" name="Q" />
        </block>
        <block symbolname="ifd" name="XLXI_5">
            <blockpin signalname="clock" name="C" />
            <blockpin signalname="SW4" name="D" />
            <blockpin signalname="LED4" name="Q" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="SW1">
            <wire x2="688" y1="1216" y2="1216" x1="656" />
        </branch>
        <iomarker fontsize="28" x="656" y="1216" name="SW1" orien="R180" />
        <branch name="clock">
            <wire x2="688" y1="1344" y2="1344" x1="656" />
        </branch>
        <iomarker fontsize="28" x="656" y="1344" name="clock" orien="R180" />
        <branch name="LED1">
            <wire x2="1088" y1="1216" y2="1216" x1="1072" />
            <wire x2="1168" y1="1072" y2="1072" x1="1088" />
            <wire x2="1088" y1="1072" y2="1216" x1="1088" />
        </branch>
        <instance x="688" y="1472" name="XLXI_1" orien="R0" />
        <instance x="672" y="1856" name="XLXI_4" orien="R0" />
        <instance x="1296" y="1488" name="XLXI_3" orien="R0" />
        <instance x="1296" y="1856" name="XLXI_5" orien="R0" />
        <branch name="SW3">
            <wire x2="672" y1="1600" y2="1600" x1="640" />
        </branch>
        <iomarker fontsize="28" x="640" y="1600" name="SW3" orien="R180" />
        <branch name="clock">
            <wire x2="672" y1="1728" y2="1728" x1="640" />
        </branch>
        <iomarker fontsize="28" x="640" y="1728" name="clock" orien="R180" />
        <branch name="LED3">
            <wire x2="1072" y1="1600" y2="1600" x1="1056" />
            <wire x2="1136" y1="1472" y2="1472" x1="1072" />
            <wire x2="1072" y1="1472" y2="1600" x1="1072" />
        </branch>
        <branch name="clock">
            <wire x2="1296" y1="1360" y2="1360" x1="1264" />
        </branch>
        <iomarker fontsize="28" x="1264" y="1360" name="clock" orien="R180" />
        <branch name="SW2">
            <wire x2="1296" y1="1232" y2="1232" x1="1264" />
        </branch>
        <iomarker fontsize="28" x="1264" y="1232" name="SW2" orien="R180" />
        <branch name="LED2">
            <wire x2="1712" y1="1232" y2="1232" x1="1680" />
        </branch>
        <iomarker fontsize="28" x="1712" y="1232" name="LED2" orien="R0" />
        <branch name="LED4">
            <wire x2="1712" y1="1600" y2="1600" x1="1680" />
        </branch>
        <iomarker fontsize="28" x="1712" y="1600" name="LED4" orien="R0" />
        <branch name="clock">
            <wire x2="1296" y1="1728" y2="1728" x1="1264" />
        </branch>
        <iomarker fontsize="28" x="1264" y="1728" name="clock" orien="R180" />
        <iomarker fontsize="28" x="1168" y="1072" name="LED1" orien="R0" />
        <branch name="SW4">
            <wire x2="1280" y1="1600" y2="1600" x1="1264" />
            <wire x2="1296" y1="1600" y2="1600" x1="1280" />
        </branch>
        <iomarker fontsize="28" x="1264" y="1600" name="SW4" orien="R180" />
        <iomarker fontsize="28" x="1136" y="1472" name="LED3" orien="R0" />
    </sheet>
</drawing>