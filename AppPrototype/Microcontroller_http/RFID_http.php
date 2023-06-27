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

                if($row['uid'] == $uid) {
                    $sql_update = "update rfid_user set last_used = '".$temp_date."' where uid = '".$uid."' ";
                    //allow entry
                    echo 1;
                }
                elseif($row['uid'] == $uid) {
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
