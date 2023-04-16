<?php

    require '1_connectDB.php';


        $nr_no = $_POST['nr_no'];
        $nr_name = $_POST['nr_name'];
        $nr_ic = $_POST['nr_ic'];
        $nr_phone = $_POST['nr_phone'];
        $start_date = $_POST['start_date'];
        $end_date = $_POST['end_date'];
        $QR = $_POST['QR'];
        $QR_id = $_POST['QR_id'];

        $counter = 0;

        $json = array();

        $sql = "insert into QR_data (nr_no, nr_name, nr_ic, nr_phone, start_date, end_date, QR , QR_id) values 
                ('".$nr_no."', '".$nr_name."', '".$nr_ic."', '".$nr_phone."', '".$start_date."', '".$end_date."', '".$QR."'
                , '".$QR_id."') ";

        //if($conn->query)

        if($conn->query($sql)){
            $json = array("status" => "success", "message" => "QR data insert successfully");

            $slq_qr_validity = "insert into QR_validity (QR_id, QR, end_date, counter) values
                                ('".$QR_id."', , '".$QR."', '".$end_date."', '".$counter."' ) ";

            $json = array("status" => "success", "message" => "QR validity data insert successfully");
        }
        else {
            $json = array("status" => "SQL error", "message" => "$conn->error" );    
        }



    echo json_encode($json, flags:JSON_PRETTY_PRINT);

    $conn->close();


?>