import java.time.LocalDateTime; // Import the LocalDateTime class
import java.time.format.DateTimeFormatter; // Import the DateTimeFormatter class
import java.util.Calendar;
import java.text.SimpleDateFormat;



public class Main {
  public static void main(String[] args) {
  
    LocalDateTime time1 = LocalDateTime.now();
    Calendar start_calendar = Calendar.getInstance();
    
    Calendar end_calendar = Calendar.getInstance();
    end_caledar.add(Calendar.DAY_OF_MONTH, 1);
    LocalDateTime time2 = time1.plusDays(1);
    
    DateTimeFormatter format1 = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    SimpleDateFormat format2 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    
    String date1 = format1.format(time1);
    String date2 = format1.format(time2);
    System.out.println(date1);
    System.out.println(date2);
    
    String date3 = format2.format(start_calendar);
    String date4 = format2.format(end_calendar);
    
    System.out.println(date3);
    System.out.println(date4);
