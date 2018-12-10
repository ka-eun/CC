import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class Friend {

   public static class MyMapper extends Mapper<LongWritable, Text, Text,Text > { //map을 상속하는 mapper class 선언 

      private Text word = new Text();
      private Text word1 = new Text();
      private Text word3 = new Text();
      private Text temp= new Text();
      private Text check= new Text();
      public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
         StringTokenizer itr = new StringTokenizer(value.toString());
         word.set(itr.nextToken());
         
         while (itr.hasMoreTokens()) { // 텍스트 파일 쪼개기 
            
            word1.set(itr.nextToken());

            if(word1.toString().compareTo(word.toString())<0) // A B 와 B A 중  A B만 남길 수 있도록 한다.
               word3.set(word1.toString()+" "+word.toString());
            else
               word3.set(word.toString()+" "+word1.toString());
            
            check.set("");
            context.write(word3, check);
         }
      }
   }

   public static class MyReducer extends Reducer<Text, Text, Text, Text> {

      private   Text tempval=new Text();
      public void reduce(Text key, Iterable<Text> values, Context context)
            throws IOException, InterruptedException {

         tempval.set("");
         context.write(key, tempval);
      }
   }

   public static void main(String[] args) {

      Configuration conf = new Configuration();
      Job job; //job 선언

      try {
         job = new Job(conf, "FriendFind");

         job.setJarByClass(Friend.class);
         job.setMapperClass(MyMapper.class);
         job.setReducerClass(MyReducer.class);
         //map reduce 클래스 및 실행 클래스 선언

         job.setOutputKeyClass(Text.class);
         job.setOutputValueClass(Text.class);
         //키 입출력 포맷 설정

         job.setInputFormatClass(TextInputFormat.class);
         job.setOutputFormatClass(TextOutputFormat.class);
         //파일 입출력 포맷 설정

         FileInputFormat.addInputPath(job, new Path(args[0]));
         FileOutputFormat.setOutputPath(job, new Path(args[1]));
         //파일 저장 위치 설정

         try {
            job.waitForCompletion(true);
         } catch (ClassNotFoundException e) {
            e.printStackTrace();
         } catch (InterruptedException e) {
            e.printStackTrace();
         }
      } catch (IOException e) {
         e.printStackTrace();
      }
   }
}
