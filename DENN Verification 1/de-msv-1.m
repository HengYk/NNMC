frame(in_file_1,in_file_2,in_file_3,v,w,r,o,x,b,y,yc,Ek,randInd,main_percent_old,main_percent_rand) and (
struct _iobuf {
char *_ptr and 
int _cnt and 
char *_base and 
int _flag and 
int _file and 
int _charbuf and 
int _bufsiz and 
char *_tmpfname 
};
FILE *in_file_1 and skip;
FILE *in_file_2 and skip;
FILE *in_file_3 and skip;
float v[3,5] and skip;
float w[5,1] and skip;
float r[5] and skip;
float o[1] and skip;
float x[3] and skip;
float b[5] and skip;
float y[1] and skip;
float yc[1] and skip;
float Ek and skip;
float main_percent_rand and skip;
float main_percent_old and skip;
struct individual {
float position[26] and 
float fitness 
};
individual randInd and skip;
 function read_param ( float *in,FILE *in_file,int RValue )
 {
     frame(read_param_buffer,read_param_1_index,read_param_1_temp,read_param_1_2_temp$_1,read_param_1_2_3_token,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     char read_param_buffer[256] and skip;
     if(in_file) then 
     {
         int read_param_1_index<==0 and skip;
         char *read_param_1_temp and skip;
         break$<==0 and skip;
         char* read_param_1_2_temp$_1 and skip;
         read_param_1_2_temp$_1:=fgets(read_param_buffer,256,in_file);
         read_param_1_temp:=read_param_1_2_temp$_1 ;
         while( break$=0 AND   ((read_param_1_temp)!=NULL) )
         {
             if(read_param_1_index>=0) then 
             {
                 char* read_param_1_2_3_token and skip;
                 read_param_1_2_3_token:=strtok(read_param_buffer,"\0",RValue);
                 in[read_param_1_index-0]:=strtod(read_param_1_2_3_token,NULL,RValue)
                 
             }
             else 
             {
                  skip 
             };
             read_param_1_index:=read_param_1_index+1;
             if(read_param_1_index=26) then 
             {
                 break$<==1 and skip
                 
             }
             else 
             {
                  skip 
             };
             read_param_1_2_temp$_1:=fgets(read_param_buffer,256,in_file);
             read_param_1_temp:=read_param_1_2_temp$_1 
         };
         break$<==0 and skip;
         if(read_param_1_temp=NULL) then 
         {
             return<==1 and RValue:=false;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             return<==1 and RValue:=true;
             skip
         }
         else
         {
             skip
         }
         
     }
     else 
     {
          skip 
     };
     if(return=0)  then
     {
         if(return=0)   then 
         {
             return<==1 and RValue:=false;
             skip
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function read_sample ( float *in,float *out,int RValue )
 {
     frame(read_sample_buffer,read_sample_1_2_temp$_1,read_sample_1_2_token,read_sample_1_2_i,read_sample_1_5_temp$_2,return) and ( 
     int return<==0 and skip;
     char read_sample_buffer[256] and skip;
     if(in_file_1 AND in_file_2) then 
     {
         char* read_sample_1_2_temp$_1 and skip;
         read_sample_1_2_temp$_1:=fgets(read_sample_buffer,256,in_file_1);
         if(read_sample_1_2_temp$_1!=NULL) then 
         {
             char* read_sample_1_2_token and skip;
             read_sample_1_2_token:=strtok(read_sample_buffer,",",RValue);
             int read_sample_1_2_i<==0 and skip;
             
             while( return=0 AND   return=0 AND   (read_sample_1_2_i<3) )
             {
                 if(read_sample_1_2_token=NULL) then 
                 {
                     fprintf(stderr,"the format of input is not correct!\n") and skip;
                     return<==1 and RValue:=false;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     in[read_sample_1_2_i]:=strtod(read_sample_1_2_token,NULL,RValue);
                     read_sample_1_2_token:=strtok(NULL,",",RValue);
                     read_sample_1_2_i:=read_sample_1_2_i+1
                 }
                 else
                 {
                     skip
                 }
                 
             }
             
         }
         else
         {
             return<==1 and RValue:=false;
             skip
         };
         if(return=0)  then
         {
             if(return=0)  then
             {
                 char* read_sample_1_5_temp$_2 and skip;
                 read_sample_1_5_temp$_2:=fgets(read_sample_buffer,256,in_file_2);
                 if(read_sample_1_5_temp$_2!=NULL) then 
                 {
                     out[0]:=strtod(read_sample_buffer,NULL,RValue)
                     
                 }
                 else
                 {
                     return<==1 and RValue:=false;
                     skip
                 };
                 if(return=0)  then
                 {
                     return<==1 and RValue:=true;
                     skip
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
         }
         else
         {
             skip
         }
         
     }
     else 
     {
          skip 
     };
     if(return=0)  then
     {
         if(return=0)   then 
         {
             return<==1 and RValue:=false;
             skip
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function score_func ( float  RValue )
 {
     frame(score_func_h,score_func_alpha_h,score_func_i,score_func_j,score_func_beta_j,score_func_h_1,return) and ( 
     int return<==0 and skip;
     int score_func_h<==0 and skip;
     
     while( (score_func_h<5) )
     {
         float score_func_alpha_h<==0 and skip;
         int score_func_i<==0 and skip;
         
         while( (score_func_i<3) )
         {
             score_func_alpha_h:=score_func_alpha_h+v[score_func_i,score_func_h]*x[score_func_i];
             score_func_i:=score_func_i+1
             
         };
         b[score_func_h]:=(1/ (1+exp(-(score_func_alpha_h-r[score_func_h]))));
         score_func_h:=score_func_h+1
         
     };
     Ek:=0;
     int score_func_j<==0 and skip;
     
     while( (score_func_j<1) )
     {
         float score_func_beta_j<==0 and skip;
         int score_func_h_1<==0 and skip;
         
         while( (score_func_h_1<5) )
         {
             score_func_beta_j:=score_func_beta_j+w[score_func_h_1,score_func_j]*b[score_func_h_1];
             score_func_h_1:=score_func_h_1+1
             
         };
         yc[score_func_j]:=(1/ (1+exp(-(score_func_beta_j-o[score_func_j]))));
         Ek:=Ek+(yc[score_func_j]-y[score_func_j])*(yc[score_func_j]-y[score_func_j]);
         score_func_j:=score_func_j+1
         
     };
     return<==1 and RValue:=0.5*Ek;
     skip
     )
     }; 
  function eval_bpnn ( float  RValue )
 {
     frame(eval_bpnn_precent,eval_bpnn_count,eval_bpnn_co,eval_bpnn_1_temp$_1,eval_bpnn_1_temp,return) and ( 
     int return<==0 and skip;
     float eval_bpnn_precent<==0.0 and skip;
     int eval_bpnn_count<==0 and skip;
     int eval_bpnn_co<==0 and skip;
     int eval_bpnn_1_temp$_1 and skip;
     eval_bpnn_1_temp$_1:=read_sample(x,y,RValue);
     while( (eval_bpnn_1_temp$_1) )
     {
         eval_bpnn_count:=eval_bpnn_count+1;
         float eval_bpnn_1_temp and skip;
         eval_bpnn_1_temp:=score_func(RValue);
         if(eval_bpnn_1_temp<0.000001) then 
         {
             eval_bpnn_co:=eval_bpnn_co+1
             
         }
         else 
         {
              skip 
         };
         eval_bpnn_1_temp$_1:=read_sample(x,y,RValue)
     };
     eval_bpnn_precent:=eval_bpnn_co/ (float)eval_bpnn_count;
     fseek(in_file_1,0,0) and skip;
     fseek(in_file_2,0,0) and skip;
     return<==1 and RValue:=eval_bpnn_precent;
     skip
     )
     }; 
  function assign_v_r_w_o ( float *val )
 {
     frame(assign_v_r_w_o_index,assign_v_r_w_o_i,assign_v_r_w_o_j,assign_v_r_w_o_i_1,assign_v_r_w_o_j_1,assign_v_r_w_o_i_2,assign_v_r_w_o_i_3) and ( 
     int assign_v_r_w_o_index<==0 and skip;
     int assign_v_r_w_o_i<==0 and skip;
     
     while( (assign_v_r_w_o_i<3) )
     {
         int assign_v_r_w_o_j<==0 and skip;
         
         while( (assign_v_r_w_o_j<5) )
         {
             v[assign_v_r_w_o_i,assign_v_r_w_o_j]:=* (val+assign_v_r_w_o_index);
             assign_v_r_w_o_index:=assign_v_r_w_o_index+1;
             assign_v_r_w_o_j:=assign_v_r_w_o_j+1
             
         };
         assign_v_r_w_o_i:=assign_v_r_w_o_i+1
         
     };
     int assign_v_r_w_o_i_1<==0 and skip;
     
     while( (assign_v_r_w_o_i_1<5) )
     {
         int assign_v_r_w_o_j_1<==0 and skip;
         
         while( (assign_v_r_w_o_j_1<1) )
         {
             w[assign_v_r_w_o_i_1,assign_v_r_w_o_j_1]:=* (val+assign_v_r_w_o_index);
             assign_v_r_w_o_index:=assign_v_r_w_o_index+1;
             assign_v_r_w_o_j_1:=assign_v_r_w_o_j_1+1
             
         };
         assign_v_r_w_o_i_1:=assign_v_r_w_o_i_1+1
         
     };
     int assign_v_r_w_o_i_2<==0 and skip;
     
     while( (assign_v_r_w_o_i_2<5) )
     {
         r[assign_v_r_w_o_i_2]:=* (val+assign_v_r_w_o_index);
         assign_v_r_w_o_index:=assign_v_r_w_o_index+1;
         assign_v_r_w_o_i_2:=assign_v_r_w_o_i_2+1
         
     };
     int assign_v_r_w_o_i_3<==0 and skip;
     
     while( (assign_v_r_w_o_i_3<1) )
     {
         o[assign_v_r_w_o_i_3]:=* (val+assign_v_r_w_o_index);
         assign_v_r_w_o_index:=assign_v_r_w_o_index+1;
         assign_v_r_w_o_i_3:=assign_v_r_w_o_i_3+1
         
     }
     )
     }; 
  function main ( int  RValue )
 {
     frame(main_percents,main_index,main_1_temp$_1,main_i,return,break$) and (
     int break$<==0 and skip;
     int return<==0 and skip;
     in_file_1:=fopen("in_reduced.txt","r");
     in_file_2:=fopen("out_reduced.txt","r");
     in_file_3:=fopen("modified_param_reduced.txt","r");
     main_percent_old<==0.910000 and skip;
     float *main_percents and skip;
     main_percents:=(float *)malloc(2*sizeof(float));
     int main_index<==0 and skip;
     int main_1_temp$_1 and skip;
     main_1_temp$_1:=read_param(randInd.position,in_file_3,RValue);
     while( (main_1_temp$_1) )
     {
         assign_v_r_w_o(randInd.position);
         main_percents[main_index]:=eval_bpnn(RValue);
         main_index:=main_index+1;
         main_1_temp$_1:=read_param(randInd.position,in_file_3,RValue)
     };
     main_percent_rand and skip;
     break$<==0 and skip;
     int main_i<==0 and skip;
     
     while( break$=0 AND   (main_i<2) )
     {
         output ("percent: ",main_percents[main_i],"\n") and skip;
         if(main_percents[main_i]>main_percent_old) then 
         {
             main_percent_rand:=main_percents[main_i];
             break$<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             main_i:=main_i+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     fclose(in_file_1) and skip;
     fclose(in_file_2) and skip;
     fclose(in_file_3) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
