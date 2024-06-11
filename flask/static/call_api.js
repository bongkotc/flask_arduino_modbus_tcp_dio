$(document).ready(function() {
    //call url ขออ่านค่าปุ่มกด
    function updateReadButtons() {
        $.ajax({
            url: '/readButtons',
            type: 'GET',
            success: function(response) {
                if(response!=null){
                    if(response.length==8){
                        let btn_ids = ['#button1','#button2','#button3','#button4','#button5','#button6','#button7','#button8']
                        
                        for (let index = 0; index < response.length; index++) {
                            $(btn_ids[index]).text((response[index]==0)?"OFF":"ON");
                        }
                    }
                }
            },
            error: function(error) {
                console.log('Error:', error);
            }
        });
    }

    //call url ขออ่านค่าหลอดไฟ
    function updateReadLeds() {
        $.ajax({
            url: '/readLeds',
            type: 'GET',
            success: function(response) {
                if(response!=null){
                    if(response.length==8){
                        let btn_ids = ['#led1','#led2','#led3','#led4','#led5','#led6','#led7','#led8']
                        
                        for (let index = 0; index < response.length; index++) {
                            $(btn_ids[index]).text((response[index]==0)?"OFF":"ON");
                            if(index==0){
                                if(response[index]==0) document.getElementById('btn_led1_off').checked = true;
                                else document.getElementById('btn_led1_on').checked = true;
                            }
                            else if(index==1){
                                if(response[index]==0) document.getElementById('btn_led2_off').checked = true;
                                else document.getElementById('btn_led2_on').checked = true;
                            }
                            else if(index==2){
                                if(response[index]==0) document.getElementById('btn_led3_off').checked = true;
                                else document.getElementById('btn_led3_on').checked = true;
                            }
                            else if(index==3){
                                if(response[index]==0) document.getElementById('btn_led4_off').checked = true;
                                else document.getElementById('btn_led4_on').checked = true;
                            }
                            else if(index==4){
                                if(response[index]==0) document.getElementById('btn_led5_off').checked = true;
                                else document.getElementById('btn_led5_on').checked = true;
                            }
                            else if(index==5){
                                if(response[index]==0) document.getElementById('btn_led6_off').checked = true;
                                else document.getElementById('btn_led6_on').checked = true;
                            }
                            else if(index==6){
                                if(response[index]==0) document.getElementById('btn_led7_off').checked = true;
                                else document.getElementById('btn_led7_on').checked = true;
                            }
                            else if(index==7){
                                if(response[index]==0) document.getElementById('btn_led8_off').checked = true;
                                else document.getElementById('btn_led8_on').checked = true;
                            }
                        }
                    }
                }
            },
            error: function(error) {
                console.log('Error:', error);
            }
        });
    }


    // timer update ทุกๆ(250 มิลลิวินาที)
    setInterval(updateReadButtons, 250);

    // timer update ทุกๆ (250 มิลลิวินาที)
    setInterval(updateReadLeds, 250);
});