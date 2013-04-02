<GO_Project support="ZHG">
    <scene>
        <text x="-835" y="-19" value="平台控制系统"/>
        <signal id="2">
            <io type="2" id="2" index="0"/>
            <io type="0" id="3" index="0"/>
        </signal>
        <signal id="1">
            <io type="2" id="1" index="0"/>
            <io type="0" id="2" index="0"/>
        </signal>
        <operator x="-601" y="70" type="1">
            <model output="1" subInput="0" input="1" type="1" id="3">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="-806" y="70" type="3">
            <model output="1" subInput="0" input="1" type="3" id="2">
                <status>
                    <status_0 description="" probability="0.1"/>
                    <status_1 description="" probability="0.8"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="-1008" y="70" type="5">
            <model output="1" subInput="0" input="0" type="5" id="1">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
    </scene>
</GO_Project>
