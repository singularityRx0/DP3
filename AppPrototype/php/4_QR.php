<?php

    require '1_connectDB.php';

    if (!empty($_POST['nr_no']) && !empty($_POST['nr_name']) && !empty($_POST['nr_ic']) && !empty($_POST['nr_phone'])) {

        //generated_by
        $gen_by = $_POST['gen_by'];

        //nr data
        $nr_no = $_POST['nr_no'];
        $nr_name = $_POST['nr_name'];
        $nr_ic = $_POST['nr_ic'];
        $nr_phone = $_POST['nr_phone'];

        //date
        $start_date = $_POST['start_date'];
        $end_date = $_POST['end_date'];

        //qr data
        $QR_id = $_POST['QR_id'];

        $counter = 0;

        $json = array();

        $sql = "insert into qr_data (gen_by, nr_no, nr_name, nr_ic, nr_phone, start_date, end_date, QR_id) values 
                ('".$gen_by."', '".$nr_no."', '".$nr_name."', '".$nr_ic."', '".$nr_phone."', 
                '".$start_date."', '".$end_date."', '".$QR_id."') ";

        //if($conn->query)

        if($conn->query($sql)){

            $sql_qr_validity = "insert into qr_validity (QR_id, start_date,end_date, counter) values
                                ('".$QR_id."', '".$start_date."', '".$end_date."', '".$counter."' ) ";

            if($conn->query($sql_qr_validity)) {
                echo "success";
            }
            else{
                echo "failed";
            }

        }
        else {
            echo "failed";
        }


    }
    else
    echo "failed";

    $conn->close();
?>
