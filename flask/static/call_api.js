$(document).ready(function() {
    $('#setLedOn').click(function() {
        $.ajax({
            url: '/mosbudWrite',
            type: 'POST',
            data: {'data':1},
            success: function(response) {
            },
            error: function(error) {
                console.log('Error:', error);
            }
        });
    });
    $('#setLedOff').click(function() {
        $.ajax({
            url: '/mosbudWrite',
            type: 'POST',
            data: {'data':0},
            success: function(response) {
            },
            error: function(error) {
                console.log('Error:', error);
            }
        });
    });
    function updateLabel() {
        $.ajax({
            url: '/readButtons',
            type: 'GET',
            success: function(response) {
                // alert(JSON.stringify(response))
                if(response!=null){
                    if(response.length==8){
                        let btn_ids = ['#button1','#button2','#button3','#button4','#button5','#button6','#button7','#button8']
                        
                        for (let index = 0; index < response.length; index++) {
                            $(btn_ids[index]).text((response[index]==0)?"OFF":"ON");
                        }
                        
                        // $('#button1').text((response[0]==0)?"OFF":"ON");
                        // $('#button2').text((response[1]==0)?"OFF":"ON");
                        // $('#button3').text((response[2]==0)?"OFF":"ON");
                        // $('#button4').text((response[3]==0)?"OFF":"ON");
                        // $('#button5').text((response[4]==0)?"OFF":"ON");
                        // $('#button6').text((response[5]==0)?"OFF":"ON");
                        // $('#button7').text((response[6]==0)?"OFF":"ON");
                        // $('#button8').text((response[7]==0)?"OFF":"ON");
                    }
                }
            },
            error: function(error) {
                console.log('Error:', error);
            }
        });
    }

    // timer update ทุกๆ 0.5 วินาที (500 มิลลิวินาที)
    setInterval(updateLabel, 250);

    // เรียกฟังก์ชันทันทีเมื่อโหลดหน้าเว็บ
    updateLabel();
});