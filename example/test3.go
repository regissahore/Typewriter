<GO_Project support="ZHG">
    <scene>
        <text x="-49.40520477294922" y="-144.9479370117188" value="设备驱动系统"/>
        <operator x="-341.1151733398438" y="65.542724609375" type="5">
            <model output="1" subInput="0" input="0" type="5" id="1">
                <status>
                    <status_0 description="" probability="0.95"/>
                    <status_1 description="" probability="0"/>
                    <status_2 description="" probability="0"/>
                    <status_3 description="" probability="0.05"/>
                </status>
            </model>
        </operator>
        <operator x="-266.8177795410156" y="-47.70260238647461" type="5">
            <model output="1" subInput="0" input="0" type="5" id="2">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="1"/>
                    <status_2 description="" probability="0"/>
                    <status_3 description="" probability="0"/>
                </status>
            </model>
        </operator>
        <operator x="-135.8698425292969" y="66.48698425292969" type="6">
            <model output="1" subInput="1" input="1" type="6" id="3">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.9"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="-57.40888595581055" y="-59.48698425292969" type="5">
            <model output="1" subInput="0" input="0" type="5" id="4">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0"/>
                    <status_2 description="" probability="1"/>
                    <status_3 description="" probability="0"/>
                </status>
            </model>
        </operator>
        <operator x="60.56508255004883" y="67.2713623046875" type="6">
            <model output="1" subInput="1" input="1" type="6" id="5">
                <status>
                    <status_0 description="" probability="0.05"/>
                    <status_1 description="" probability="0.85"/>
                    <status_2 description="" probability="0.1"/>
                </status>
            </model>
        </operator>
        <operator x="246.5464019775391" y="67.15987396240234" type="1">
            <model output="1" subInput="0" input="1" type="1" id="6">
                <status>
                    <status_0 description="" probability="0"/>
                    <status_1 description="" probability="0.8"/>
                    <status_2 description="" probability="0.2"/>
                </status>
            </model>
        </operator>
        <signal id="1">
            <io type="2" id="1" index="0"/>
            <io type="0" id="3" index="0"/>
        </signal>
        <signal id="2">
            <io type="2" id="2" index="0"/>
            <io type="1" id="3" index="0"/>
        </signal>
        <signal id="3">
            <io type="2" id="3" index="0"/>
            <io type="0" id="5" index="0"/>
        </signal>
        <signal id="4">
            <io type="2" id="4" index="0"/>
            <io type="1" id="5" index="0"/>
        </signal>
        <signal id="5">
            <io type="2" id="5" index="0"/>
            <io type="0" id="6" index="0"/>
        </signal>
    </scene>
</GO_Project>
