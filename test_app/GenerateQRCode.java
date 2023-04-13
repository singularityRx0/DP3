package com.example.test_app;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.media.Image;
import android.nfc.Tag;
import android.os.Build;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Environment;
import android.text.TextUtils;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.Manifest;

import com.google.android.material.tabs.TabLayout;
import com.google.android.material.textfield.TextInputEditText;
import com.google.zxing.WriterException;

import org.json.JSONException;
import org.json.JSONObject;

import java.lang.reflect.Array;
import java.sql.Time;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Objects;
import java.util.concurrent.TimeUnit;

import androidmads.library.qrgenearator.QRGContents;
import androidmads.library.qrgenearator.QRGEncoder;
import androidmads.library.qrgenearator.QRGSaver;
import kotlin.collections.UArraySortingKt;

public class GenerateQRCode extends AppCompatActivity {

    ImageView imageView;
    TextView textViewTimer;
    TextInputEditText textInputEditTextNoVisitors, textInputEditTextNameVisitor, textInputEditTextIcNoVisitor, textInputEditTextHpNo;
    Button buttonGenerateQR, buttondownload;
    String savePath = Environment.getExternalStorageDirectory().getPath() + "/QRCode/";

    Bitmap bitmap;

    String Content;
    AppCompatActivity activity;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_generate_qrcode);

        activity = this;

        imageView = findViewById(R.id.idIVQrcode);
        textViewTimer = findViewById(R.id.timer_QR);
        textInputEditTextNoVisitors = findViewById(R.id.Num_Visit_QR);
        textInputEditTextNameVisitor = findViewById(R.id.Name_QR);
        textInputEditTextIcNoVisitor = findViewById(R.id.IC_QR);
        textInputEditTextHpNo = findViewById(R.id.Hp_QR);
        buttonGenerateQR = findViewById(R.id.btn_generate);
        buttondownload = findViewById(R.id.btn_download);

        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            savePath = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS).getPath() + "/QRCode/";
        }

        buttonGenerateQR.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String NoVisitor = String.valueOf(textInputEditTextNoVisitors.getText());
                String NameVisitor = String.valueOf(textInputEditTextNameVisitor.getText());
                String IcVisitor = String.valueOf(textInputEditTextIcNoVisitor.getText());
                String HpVisitor = String.valueOf(textInputEditTextHpNo.getText());


                Calendar start_calender = Calendar.getInstance();
                Calendar end_calender = Calendar.getInstance();


                Log.i("Date", start_calender.toString());
                Log.i("Date1", end_calender.toString());

                //end_calender.set(year, month, date, hourofday, minute, second)
                //add one day to start date
                end_calender.add(Calendar.DAY_OF_MONTH, 1);


                //String Json_start_calender = dateFormat.format(start_calender);
                //String Json_end_calender = dateFormat.format(end_calender);

                textViewTimer.setVisibility(View.VISIBLE);

                long start_millis = start_calender.getTimeInMillis(); //get time in miliseconds
                long end_millis = end_calender.getTimeInMillis();
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


                    @SuppressLint("SetTextI18n")
                    @Override
                    public void onFinish() {
                        textViewTimer.setText("QR CODE EXPIRED");
                    }
                };
                cdt.start();


                if(TextUtils.isEmpty(NoVisitor)) {
                    Toast.makeText(GenerateQRCode.this, "This is required", Toast.LENGTH_SHORT).show();
                }
                else {
                    imageView.setVisibility(View.VISIBLE);
                    textInputEditTextNoVisitors.setVisibility(View.GONE);
                    textInputEditTextNameVisitor.setVisibility(View.GONE);
                    textInputEditTextIcNoVisitor.setVisibility(View.GONE);
                    textInputEditTextHpNo.setVisibility(View.GONE);
                    buttonGenerateQR.setVisibility(View.GONE);
                    WindowManager manager = (WindowManager) getSystemService(WINDOW_SERVICE);

                    Display display = manager.getDefaultDisplay();

                    Point point = new Point();
                    display.getSize(point);

                    int width = point.x;
                    int height = point.y;
                    int dime = Math.min(width, height);

                    JSONObject jsonObject = new JSONObject();

                    try {
                        jsonObject.put("No Visitor", NoVisitor);
                        jsonObject.put("Visitor Name", NameVisitor);
                        jsonObject.put("IC Number", IcVisitor);
                        jsonObject.put("Phone Number", HpVisitor);
                        //jsonObject.put("Start Date", date);
                        //jsonObject.put("End Date", Json_end_calender);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }

                    //String compiled = jsonObject.toString();

                    Log.i("mytag", jsonObject.toString());

                    Content = jsonObject.toString();

                    QRGEncoder qrgEncoder = new QRGEncoder(jsonObject.toString(), null, QRGContents.Type.TEXT, dime);
                    try {
                        bitmap = qrgEncoder.getBitmap(0);
                        imageView.setImageBitmap(bitmap);
                    } catch(Exception e) {
                        Log.v("Tag", e.toString());
                    }

                    buttondownload.setVisibility(View.VISIBLE);
                    buttondownload.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            if (ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED) {
                                try {
                                    boolean save = new QRGSaver().save(savePath, Content.trim(), bitmap, QRGContents.ImageType.IMAGE_JPEG);
                                    String result = save ? "Image Saved" : "Image Not Saved";
                                    Toast.makeText(activity, result, Toast.LENGTH_LONG).show();
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            } else {
                                ActivityCompat.requestPermissions(activity, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0);
                            }
                        }
                    });

                }

            }
        });

    }
}