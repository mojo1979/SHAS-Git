        function submitCommandBtn() {
                const urlParams = new URLSearchParams(window.location.search);
                const sessionParam = urlParams.get('session');
                const keyParam = urlParams.get('key');
		const facCommand = $('#fac_com_field').val();
                $.get('/controller?session=' + sessionParam + '&key=' + keyParam + '&update=actuators' + '&faccomm=' + facCommand, function(data, stat) {
			$('#commandMsg').text(data);
                });
        }

$('document').ready(function() {
	setInterval(function() {
                const urlParams = new URLSearchParams(window.location.search);
		const sessionParam = urlParams.get('session');
		const keyParam = urlParams.get('key');
		$.get('/controller?session=' + sessionParam + '&key=' + keyParam + '&update=sensors', function(data, stat) {
			const sensorArrayFAC = JSON.parse(data).ACVals[0].Sensors;
			const sensorArrayLAC = JSON.parse(data).ACVals[1].Sensors;
			const sensorArrayBEAC = JSON.parse(data).ACVals[2].Sensors;
			const sensorArrayBAC = JSON.parse(data).ACVals[3].Sensors;
			$('#T0R0C0').text(sensorArrayFAC[0].SensId);
			$('#T0R0C1').text(sensorArrayFAC[0].SensType);
			$('#T0R0C2').text(sensorArrayFAC[0].SensVal);
                        $('#T0R1C0').text(sensorArrayFAC[1].SensId);
                        $('#T0R1C1').text(sensorArrayFAC[1].SensType);
                        $('#T0R1C2').text(sensorArrayFAC[1].SensVal);
                        $('#T0R2C0').text(sensorArrayFAC[2].SensId);
                        $('#T0R2C1').text(sensorArrayFAC[2].SensType);
                        $('#T0R2C2').text(sensorArrayFAC[2].SensVal);
                        $('#T0R3C0').text(sensorArrayFAC[3].SensId);
                        $('#T0R3C1').text(sensorArrayFAC[3].SensType);
                        $('#T0R3C2').text(sensorArrayFAC[3].SensVal);
 			$('#T1R0C0').text(sensorArrayLAC[0].SensId);
                        $('#T1R0C1').text(sensorArrayLAC[0].SensType);
                        $('#T1R0C2').text(sensorArrayLAC[0].SensVal);
                        $('#T1R1C0').text(sensorArrayLAC[1].SensId);
                        $('#T1R1C1').text(sensorArrayLAC[1].SensType);
                        $('#T1R1C2').text(sensorArrayLAC[1].SensVal);
                        $('#T1R2C0').text(sensorArrayLAC[2].SensId);
                        $('#T1R2C1').text(sensorArrayLAC[2].SensType);
                        $('#T1R2C2').text(sensorArrayLAC[2].SensVal);
                        $('#T1R3C0').text(sensorArrayLAC[3].SensId);
                        $('#T1R3C1').text(sensorArrayLAC[3].SensType);
                        $('#T1R3C2').text(sensorArrayLAC[3].SensVal);
 			$('#T2R0C0').text(sensorArrayBEAC[0].SensId);
                        $('#T2R0C1').text(sensorArrayBEAC[0].SensType);
                        $('#T2R0C2').text(sensorArrayBEAC[0].SensVal);
                        $('#T2R1C0').text(sensorArrayBEAC[1].SensId);
                        $('#T2R1C1').text(sensorArrayBEAC[1].SensType);
                        $('#T2R1C2').text(sensorArrayBEAC[1].SensVal);
                        $('#T2R2C0').text(sensorArrayBEAC[2].SensId);
                        $('#T2R2C1').text(sensorArrayBEAC[2].SensType);
                        $('#T2R2C2').text(sensorArrayBEAC[2].SensVal);
                        $('#T2R3C0').text(sensorArrayBEAC[3].SensId);
                        $('#T2R3C1').text(sensorArrayBEAC[3].SensType);
                        $('#T2R3C2').text(sensorArrayBEAC[3].SensVal);
 			$('#T3R0C0').text(sensorArrayBAC[0].SensId);
                        $('#T3R0C1').text(sensorArrayBAC[0].SensType);
                        $('#T3R0C2').text(sensorArrayBAC[0].SensVal);
                        $('#T3R1C0').text(sensorArrayBAC[1].SensId);
                        $('#T3R1C1').text(sensorArrayBAC[1].SensType);
                        $('#T3R1C2').text(sensorArrayBAC[1].SensVal);
                        $('#T3R2C0').text(sensorArrayBAC[2].SensId);
                        $('#T3R2C1').text(sensorArrayBAC[2].SensType);
                        $('#T3R2C2').text(sensorArrayBAC[2].SensVal);
                        $('#T3R3C0').text(sensorArrayBAC[3].SensId);
                        $('#T3R3C1').text(sensorArrayBAC[3].SensType);
                        $('#T3R3C2').text(sensorArrayBAC[3].SensVal);
		});
	}, 500);
});
