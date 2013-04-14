<GO_Project support="ZHG">
    <scene>
        <text x="-111" y="-147" value="电源开关系统"/>
        <operator x="-250" y="15" type="5">
            <model output="1" subInput="0" input="0" type="5" id="1">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="-166" y="-97" type="5">
            <model output="1" subInput="0" input="0" type="5" id="2">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="-57" y="-9" type="6">
            <model output="1" subInput="1" input="1" type="6" id="3">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="-60" y="98" type="1">
            <model output="1" subInput="0" input="1" type="1" id="4">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="118.3457641601562" y="43.51571655273438" type="2">
            <model output="1" subInput="0" input="2" type="2" id="5">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0"/>
                    <status_2 description="" probability="0"/>
                </status>
            </model>
        </operator>
        <signal id="1">
            <io type="2" id="1" index="0"/>
            <io type="0" id="3" index="0"/>
        </signal>
        <signal id="2">
            <io type="2" id="1" index="0"/>
            <io type="0" id="4" index="0"/>
        </signal>
        <signal id="3">
            <io type="2" id="2" index="0"/>
            <io type="1" id="3" index="0"/>
        </signal>
        <signal id="4">
            <io type="2" id="3" index="0"/>
            <io type="0" id="5" index="0"/>
        </signal>
        <signal id="5">
            <io type="2" id="4" index="0"/>
            <io type="0" id="5" index="1"/>
        </signal>
    </scene>
</GO_Project>
