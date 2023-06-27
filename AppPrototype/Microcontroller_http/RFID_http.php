<?php
//retrieve data from microcontroller check with mysql 
    date_default_timezone_set("Asia/Kuala_Lumpur");
    require '1_connectDB.php';

    //device key value
    $device_key_value = "123";


    if($_SERVER["REQUEST_METHOD"] == "POST") {
        $device_key = test_input($_POST['device_key']);

        if($device_key_value == $device_key) {
            $uid = test_input($_POST['uid']);

            $sql = "select * from rfid_user where uid = '".$uid."'";
            $res = $conn->query($sql);

            if($res->num_rows != 0) {
                $row = $res->fetch_assoc();
            
                //time variable
                //sever time
                $current_time = date_create(date("Y-m-d H:i:s"));
                $temp_date = $current_time->format("Y-m-d H:i:s");
                //$current_time_database = $current_time->format("Y-m-d H:i:s");
                //QR end time

                if($row['uid'] == $uid || $row['uid'] == $uid && $row['status'] == "exit") {
                    //allow entry
                    echo 1;
                    $status = "entry";
                    $status_log = "open";
                    $sql_update = "update rfid_user set last_used = '".$temp_date."' and status = '".$status."'
                    where uid = '".$uid."' ";
                    if($conn->query($sql_update)) {
                        $sql_log = "insert into rfid_log (uid, entry_date, status_log) values
                        ('".$uid."', '".$temp_date."', '".$status_log."')";
                        $conn->query($sql_log);
                    }
                }
                elseif($row['uid'] == $uid && $row['status'] == "entry") {
                    //allow exit
                    echo 4;
                    $status = "exit";
                    $status_log = "closed";
                    $sql_update = "update rfid_user set last_used = '".$temp_date."' and status = '".$status."'
                    where uid = '".$uid."' ";
                    if($conn->query($sql_update)) {
                        $sql_log = "update rfid_log set exit_date = '".$temp_date."' , status_log = '".$status_log."' where 
                        uid = '".$uid."' and status_log = '"."open"."' ";
                        $conn->query($sql_log);
                    }
                }
                elseif($row['uid'] != $uid) {
                    //allow entry
                    echo 0;
                }
            }
            else
            //UID does not exist
            echo 2;
        }
        else
        //device id not the same 
        echo 3;
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
