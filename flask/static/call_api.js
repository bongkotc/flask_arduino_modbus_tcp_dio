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
            url: '/mosbudRead',
            type: 'GET',
            success: function(response) {
                if(response[0]==0){
                    $('#dataLabel').text("OFF");
                }
                else if(response[0]==1){
                    $('#dataLabel').text("ON");
                }
            },
            error: function(error) {
                console.log('Error:', error);
            }
        });
    }

    // timer update ทุกๆ 0.5 วินาที (500 มิลลิวินาที)
    setInterval(updateLabel, 500);

    // เรียกฟังก์ชันทันทีเมื่อโหลดหน้าเว็บ
    updateLabel();
});