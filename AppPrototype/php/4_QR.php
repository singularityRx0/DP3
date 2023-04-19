<?php

    require '1_connectDB.php';

    if (!empty($_POST['nr_no']) && !empty($_POST['nr_name']) && !empty($_POST['nr_ic']) && !empty($_POST['nr_phone'])) {

        //nr data
        $nr_no = $_POST['nr_no'];
        $nr_name = $_POST['nr_name'];
        $nr_ic = $_POST['nr_ic'];
        $nr_phone = $_POST['nr_phone'];

        //date
        $start_date = $_POST['start_date'];
        $end_date = $_POST['end_date'];

        //qr data
        $QR = $_POST['QR'];
        $QR_id = $_POST['QR_id'];

        //generated_by
        $gen_by = $_POST['gen_by'];

        $counter = 0;

        $json = array();

        $sql = "insert into QR_data (gen_by, nr_no, nr_name, nr_ic, nr_phone, start_date, end_date, QR , QR_id) values 
                ('".$gen_by."', '".$nr_no."', '".$nr_name."', '".$nr_ic."', '".$nr_phone."', 
                '".$start_date."', '".$end_date."', '".$QR."', '".$QR_id."') ";

        //if($conn->query)

        if($conn->query($sql)){

            $slq_qr_validity = "insert into QR_validity (QR_id, QR, start_date,end_date, counter) values
                                ('".$QR_id."', , '".$QR."', '".$start_date."', '".$end_date."', '".$counter."' ) ";

            if($conn->query($slq_qr_validity)) {
                $json = array("status" => "QR success", "message" => "QR validity data insert successfully");
            }
            else{
                $json = array("status" => "QR failed", "message" => "Failed to insert into QR_validity");
            }

        }
        else {
            $json = array("status" => "SQL insert error", "message" => "");    
        }


    }
    else
    $json = array("status" => "failed", "message" => "All fields are required"); 



    echo json_encode($json, flags:JSON_PRETTY_PRINT);

    $conn->close();
?>
