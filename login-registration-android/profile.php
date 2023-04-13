<?php
if (!empty($_POST['email']) && !empty($_POST['apikey'])) {
    $con = mysqli_connect(hostname:"localhost" , username:"root" , password:"012862871105232000lzH@" ,database:"login_register");

    $email = $_POST['email'];
    $apikey = $_POST['apikey']; 
    $result = array();    

    if($con) {
        $sql = "select * from users where email = '".$email."' and apikey = '".$apikey."' ";
        $res = mysqli_query($con,$sql);

        if (mysqli_num_rows($res) != 0) {
            $row = mysqli_fetch_assoc($res);
            $result = array("status" => "success", "message" => "Data fetched successfully", 
            "name" => $row['name'], "email" => $row['email'], "apikey" => $row['apikey']);
        }
        else
        $result = array("status" => "failed", "message" => "Unauthorised access");
    }
    else
    $result = array("status" => "failed", "message" => "Database connecion failed");

    mysqli_close($con);
}
else
$result = array("status" => "failed", "message" => "All fileds required");

echo json_encode($result, flags:JSON_PRETTY_PRINT);

?>