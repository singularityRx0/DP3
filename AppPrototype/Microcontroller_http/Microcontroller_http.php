<?php
//retrieve data from microcontroller check with mysql 
    date_default_timezone_set("Asia/Kuala_Lumpur");
    require '1_connectDB.php';

    //device key value
    $device_key_value = "123";


    if($_SERVER["REQUEST_METHOD"] == "POST") {
        $device_key = test_input($_POST['device_key']);

        if($device_key_value == $device_key) {
            $QR_id = test_input($_POST['QR_id']);
            $start_date = test_input($_POST['start_date']);
            $end_date = test_input($_POST['end_date']);

            $sql = "select * from QR_validity where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
            $res = $conn->query($sql);

            if($res->num_rows != 0) {
                $row = $res->fetch_assoc();
            
                //time variable
                //sever time
                $current_time = date_create(date("Y-m-d H:i:s"));
                $temp_date = $current_time->format("Y-m-d H:i:s");
                //$current_time_database = $current_time->format("Y-m-d H:i:s");
                //QR end time
                $QRend_time = date_create($row['end_date']);

                //remaining time
                $remain_time = date_diff($current_time,$QRend_time);
                $remain_day = (int)$remain_time->format("%R%a");
                $remain_hour = (int)$remain_time->format("%R%h");
                $remain_min = (int)$remain_time->format("%R%i");
                $remain_sec = (int)$remain_time->format("%R%s");

                if($remain_day >= 0 && $remain_hour >= 0 && $remain_min >= 0 && $remain_sec >= 0) {
                    //if qr counter is 0 allow entry(1) and update qr to 1 for single use only.
                    // if qr counter is 1 do not allow entry(0)
                    if($row['counter'] == 0) {
                        $counter = 1;
                        $status = "Used-Entry";
                        $sql_update = "update qr_validity set counter = '".$counter."' , status = '".$status."' , used_by = '".$temp_date."'
                        where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
                        if ($conn->query($sql_update)){
                            //entry allowed
                            echo 1;
                            $sql_qr_log = " insert into qr_log (QR_id, start_date, end_date) values
                            ('".$QR_id."','".$start_date."','".$end_date."') ";
                            $conn->query($sql_qr_log);
                        }
                    }
                    elseif ($row['counter'] == 1 && $row['status'] != "Used-Entry") {
                        //entry denied
                        echo 0;
                    }
                    elseif ($row['counter'] == 1 && $row['status'] == "Used-Entry") {
                        //Allow exit
                        echo 5;
                        $status = "Used-Exit";
                        $sql_update = "update qr_validity set status = '".$status."' , used_by = '".$temp_date."'
                        where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
                        $conn->query($sql_update);
                    }
                    
                }
                elseif ($remain_day < 0 && $remain_hour < 0 && $remain_min < 0 && $remain_sec < 0) {
                //QR code expired
                $status = "Expired";
                $sql_update = "update qr_validity set status = '".$status."' 
                where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
                $conn->query($sql_update);
                echo 2;
                }
            }
            else
            //QR code does not exist
            echo 3;
        }
        else
        //device id not the same 
        echo 4;
    }
    else
    echo "Not post method";

    $conn->close();


    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }


?>
