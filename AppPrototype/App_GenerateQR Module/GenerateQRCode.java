package com.example.appprototype1;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Environment;
import android.provider.Settings;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.material.textfield.TextInputEditText;

import org.json.JSONException;
import org.json.JSONObject;

import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.TimeUnit;

import androidmads.library.qrgenearator.QRGContents;
import androidmads.library.qrgenearator.QRGEncoder;
import androidmads.library.qrgenearator.QRGSaver;


public class GenerateQRCode extends AppCompatActivity {

    private static final String ALLOWED_CHARACTERS ="0123456789qwertyuiopasdfghjklzxcvbnm";

    private static String getRandomString(final int sizeOfRandomString)
    {
        final Random random=new Random();
        final StringBuilder sb=new StringBuilder(sizeOfRandomString);
        for(int i=0;i<sizeOfRandomString;++i)
            sb.append(ALLOWED_CHARACTERS.charAt(random.nextInt(ALLOWED_CHARACTERS.length())));
        return sb.toString();
    }

    private TextInputEditText textInputEditTextNrNo, textInputEditTextNrName, textInputEditTextNrIc, textInputEditTextNrPhone;
    private ImageView qrImage;
    private TextView textViewTimer, textViewError;
    private String inputValue, nr_no, nr_name, nr_ic, nr_phone, start_date, end_date, QR_id, gen_by, start_date_phone;
    private String savePath = Environment.getExternalStorageDirectory().getPath() + "/QRCode/";
    private Bitmap bitmap;
    private QRGEncoder qrgEncoder;
    private AppCompatActivity activity;

    SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_generate_qrcode);

        qrImage = findViewById(R.id.QRcodeview);

        textInputEditTextNrNo = findViewById(R.id.nr_no);
        textInputEditTextNrName = findViewById(R.id.nr_name);
        textInputEditTextNrIc = findViewById(R.id.nr_ic);
        textInputEditTextNrPhone = findViewById(R.id.nr_phone);

        textViewTimer = findViewById(R.id.timer);
        textViewError = findViewById(R.id.error);

        Button buttonSubmit = findViewById(R.id.submit);
        Button buttonDownload = findViewById(R.id.download);

        activity = this;

        sharedPreferences = getSharedPreferences("MyAppName", MODE_PRIVATE);
        if (sharedPreferences.getString("logged", "false").equals("false")) {
            Intent intent = new Intent(getApplicationContext(), Login.class);
            startActivity(intent);
            finish();
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            savePath = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS).getPath() + "/QRCode/";
//            try {
//                Intent intent  = new Intent(Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION);
//                intent.addCategory("android.intent.category.DEFAULT");
//                intent.setData(Uri.parse(String.format("package:%s",getApplicationContext().getPackageName())));
//                startActivity(intent);
//            } catch (Exception e) {
//                Intent intent = new Intent();
//                intent.setAction(Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION);
//                startActivity(intent);
//            }
        }


        buttonSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                RequestQueue queue = Volley.newRequestQueue(getApplicationContext());
                String url = "http://192.168.0.108/AppPrototype/4_QR.php";

                textInputEditTextNrNo.setVisibility(View.GONE);
                textInputEditTextNrName.setVisibility(View.GONE);
                textInputEditTextNrIc.setVisibility(View.GONE);
                textInputEditTextNrPhone.setVisibility(View.GONE);
                buttonSubmit.setVisibility(View.GONE);
                buttonDownload.setVisibility(View.GONE);
                qrImage.setVisibility(View.VISIBLE);
                textViewTimer.setVisibility(View.VISIBLE);

                nr_no = String.valueOf(textInputEditTextNrNo.getText());
                nr_name = String.valueOf(textInputEditTextNrName.getText());
                nr_ic = String.valueOf(textInputEditTextNrIc.getText());
                nr_phone = String.valueOf(textInputEditTextNrPhone.getText());

                gen_by = sharedPreferences.getString("name","");

                Calendar start_calendar = Calendar.getInstance();
                Calendar end_calendar = Calendar.getInstance();
                end_calendar.add(Calendar.DAY_OF_MONTH,1);

                SimpleDateFormat format_database = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                SimpleDateFormat format_phone = new SimpleDateFormat("yyyy_MM_dd_HH_mm_ss");

                String date_database1 = format_database.format(start_calendar.getTime());
                String date_database2 = format_database.format(end_calendar.getTime());
                String date_phone1 = format_phone.format(start_calendar.getTime());
                String date_phone2 = format_phone.format(end_calendar.getTime());

                start_date = date_database1;
                end_date = date_database2;
                start_date_phone = date_phone1;

                Log.i("date1", date_database1);
                Log.i("date2", date_database2);
                Log.i("date1", date_phone1);
                Log.i("date2", date_phone2);

                long start_millis = start_calendar.getTimeInMillis(); //get time in miliseconds
                long end_millis = end_calendar.getTimeInMillis();
                long total_millis = (end_millis-start_millis);

                //count down by 1 sec
                CountDownTimer cdt = new CountDownTimer(total_millis,1000) {
                    @SuppressLint("SetTextI18n")
                    @Override
                    public void onTick(long millisUntilFinished) {

                        //set format to 00:00:00:00
                        NumberFormat f = new DecimalFormat("00");
                        long days = TimeUnit.MILLISECONDS.toDays(millisUntilFinished);
                        millisUntilFinished -= TimeUnit.DAYS.toMillis(days);

                        long hours = TimeUnit.MILLISECONDS.toHours(millisUntilFinished);
                        millisUntilFinished -= TimeUnit.HOURS.toMillis(hours);

                        long min = TimeUnit.MILLISECONDS.toMinutes(millisUntilFinished);
                        millisUntilFinished -= TimeUnit.MINUTES.toMillis(min);

                        long sec = TimeUnit.MILLISECONDS.toSeconds(millisUntilFinished);


                        textViewTimer.setText(f.format(days) + ":" + f.format(hours) + ":" + f.format(min) + ":" + f.format(sec));
                    }

                    @Override
                    public void onFinish() {
                        textViewTimer.setText("QR CODE EXPIRED");
                    }
                };
                cdt.start();

                QR_id = getRandomString(12);
                Log.i("gen_by", gen_by);
                Log.i("QR_id", QR_id);

                JSONObject jsonObject = new JSONObject();
                try {
                    jsonObject.put("QR_id", QR_id);
                    jsonObject.put("start_date", start_date);
                    jsonObject.put("end_date", end_date);
                } catch (JSONException e) {
                    e.printStackTrace();
                }

                inputValue = jsonObject.toString();
                Log.i("inputvalue", inputValue);

                WindowManager manager = (WindowManager) getSystemService(WINDOW_SERVICE);
                Display display = manager.getDefaultDisplay();
                Point point = new Point();
                display.getSize(point);
                int width = point.x;
                int height = point.y;
                int smallerDimension = Math.min(width,height);
                smallerDimension = smallerDimension * 3/4;

                qrgEncoder = new QRGEncoder(inputValue, null, QRGContents.Type.TEXT, smallerDimension);
                try{
                    bitmap = qrgEncoder.getBitmap(0);
                    qrImage.setImageBitmap(bitmap);
                }catch (Exception e) {
                    e.printStackTrace();
                }


                StringRequest stringRequest = new StringRequest(Request.Method.POST, url,
                        new Response.Listener<String>() {
                            @Override
                            public void onResponse(String response) {
                                if(response.equals("success")) {
                                    Toast.makeText(getApplicationContext(), "QR code generated", Toast.LENGTH_SHORT).show();
                                    buttonDownload.setVisibility(View.VISIBLE);
                                }
                                else {
                                    textViewError.setText(response);
                                    textViewError.setVisibility(View.VISIBLE);
                                }
                            }
                        }, new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        textViewError.setText(error.getLocalizedMessage());
                        textViewError.setVisibility(View.VISIBLE);
                    }
                }) {
                    protected Map<String, String> getParams() {
                        Map<String, String> paramV = new HashMap<>();
                        paramV.put("gen_by", gen_by);
                        paramV.put("nr_no", nr_no);
                        paramV.put("nr_name", nr_name);
                        paramV.put("nr_ic", nr_ic);
                        paramV.put("nr_phone", nr_phone);
                        paramV.put("start_date", start_date);
                        paramV.put("end_date", end_date);
                        paramV.put("QR_id", QR_id );
                        return paramV;
                    }
                };
                queue.add(stringRequest);
            }
        });

        buttonDownload.setOnClickListener(v -> {

            String currentDateandTime = start_date_phone;
            Log.i("Current data and time", currentDateandTime);

            if (ContextCompat.checkSelfPermission(getApplicationContext(), android.Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) {
                try {
                    boolean save = new QRGSaver().save(savePath, currentDateandTime, bitmap, QRGContents.ImageType.IMAGE_JPEG);
                    String result = save ? "Image Saved" : "Image Not Saved";
                    Toast.makeText(activity, result, Toast.LENGTH_LONG).show();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else {
                ActivityCompat.requestPermissions(activity, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0);
            }
        });

    }
}
