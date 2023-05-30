<?php

    date_default_timezone_set("Asia/Kuala_Lumpur");
    require "1_connectDB.php";

    $current_time = date_create(date("Y-m-d H:i:s"));
    $temp_date = $current_time->format("Y-m-d H:i:s");

    $device_key_value = "123";

    if($_SERVER["REQUEST_METHOD"]=='POST') {

        if ($device_key_value ==test_input($_POST['device_key'])) {

            $QR_id = test_input($_POST['QR_id']);
            $start_date = test_input($_POST['start_date']);
            $end_date = test_input($_POST['end_date']);

            $sql = " insert into qr_log (QR_id, start_date, end_date) values
            ('".$QR_id."','".$start_date."','".$end_date."') ";

            if ($conn->query($sql)) {

                $sql_lookup = "select * from qr_log where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
                $res = $conn->query($sql_lookup);

                if($res->num_rows != 0) {
                    $row = $res->fetch_assoc();

                    if($row['entry_date'] == "0000-00-00 00:00:00" && $row['exit_date'] == "0000-00-00 00:00:00")
                    {
                        $sql_qr_log = "update qr_log set entry_date = '".$temp_date."' 
                        where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
                        if ($conn->query($sql_qr_log)) {
                            echo 1;
                        }

                    }

                    elseif($row['entry_date'] != "0000-00-00 00:00:00" && $row['exit_date'] == "0000-00-00 00:00:00")
                    {
                        $sql_qr_log = "update qr_log set exit_date = '".$temp_date."' 
                        where QR_id = '".$QR_id."' and start_date = '".$start_date."' and end_date = '".$end_date."' ";
                        if ($conn->query($sql_qr_log)) {
                            echo 2;
                        }

                    }
                    elseif($row['entry_date'] != "0000-00-00 00:00:00" && $row['exit_date'] != "0000-00-00 00:00:00") {
                        echo 3;
                        $conn->close();
                    }
                }
            }

        }

        $conn->close();
    }




    function test_input($data) {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }

?>
