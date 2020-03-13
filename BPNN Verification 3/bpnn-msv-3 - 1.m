frame(v,w,r,o,g,e,f,x,b,y,yc,Ek,aveEk,bpnn_sim_single_Ek_,bpnn_sim_single_Ek_out,bpnn_sim_single_iter,l2) and (
float l2 <== 0.0 and 
float Ek <== 0.00007368 and 
float bpnn_sim_single_Ek_ <== Ek and 
float bpnn_sim_single_Ek_out <== 1.0 and 
float aveEk <== 0.00000215 and 
int bpnn_sim_single_iter <== 0 and skip;

float v[3,5] and skip;
float w[5,1] and skip;
float r[5] and skip;
float o[1] and skip;
float g[1] and skip;
float e[5] and skip;
float f[3] and skip;
float x[3] and skip;
float b[5] and skip;
float y[1] and skip;
float yc[1] and skip;
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
 function read_parameter ( int  RValue )
 {
     frame(read_parameter_in,read_parameter_buffer,read_parameter_i,read_parameter_h,read_parameter_h_1,read_parameter_j,read_parameter_h_2,read_parameter_j_1,return) and ( 
     int return<==0 and skip;
     FILE *read_parameter_in<==NULL and skip;
     read_parameter_in:=fopen("bpnn_param.txt","r");
     if(read_parameter_in=NULL) then 
     {
         fprintf(stderr,"Cannot open %s\n","bpnn_param.txt") and skip;
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         char read_parameter_buffer[256] and skip;
         int read_parameter_i<==0 and skip;
         
         while( (read_parameter_i<3) )
         {
             int read_parameter_h<==0 and skip;
             
             while( (read_parameter_h<5) )
             {
                 fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
                 v[read_parameter_i,read_parameter_h]:=strtod(read_parameter_buffer,NULL,RValue);
                 
                 // output(v[read_parameter_i,read_parameter_h], "\n") and skip;
                 
                 read_parameter_h:=read_parameter_h+1
                 
             };
             read_parameter_i:=read_parameter_i+1
             
         };
         int read_parameter_h_1<==0 and skip;
         
         while( (read_parameter_h_1<5) )
         {
             int read_parameter_j<==0 and skip;
             
             while( (read_parameter_j<1) )
             {
                 fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
                 w[read_parameter_h_1,read_parameter_j]:=strtod(read_parameter_buffer,NULL,RValue);
                 read_parameter_j:=read_parameter_j+1
                 
             };
             read_parameter_h_1:=read_parameter_h_1+1
             
         };
         int read_parameter_h_2<==0 and skip;
         
         while( (read_parameter_h_2<5) )
         {
             fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
             r[read_parameter_h_2]:=strtod(read_parameter_buffer,NULL,RValue);
             read_parameter_h_2:=read_parameter_h_2+1
             
         };
         int read_parameter_j_1<==0 and skip;
         
         while( (read_parameter_j_1<1) )
         {
             fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
             o[read_parameter_j_1]:=strtod(read_parameter_buffer,NULL,RValue);
             read_parameter_j_1:=read_parameter_j_1+1
             
         };
         fclose(read_parameter_in) and skip;
         return<==1 and RValue:=1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function bpnn_sim_single (  )
 {
    frame(bpnn_sim_single_ax,bpnn_sim_single_by,bpnn_sim_single_1_h,bpnn_sim_single_1_alpha_h,bpnn_sim_single_1_i,bpnn_sim_single_1_j,bpnn_sim_single_1_beta_j,bpnn_sim_single_1_h_1,bpnn_sim_single_1_j_1,bpnn_sim_single_1_j_2,bpnn_sim_single_1_h_2,bpnn_sim_single_1_temp,bpnn_sim_single_1_j_3,bpnn_sim_single_1_i_1,bpnn_sim_single_1_temp1,bpnn_sim_single_1_h_3,bpnn_sim_single_1_i_2,bpnn_sim_single_check_attack,break$) and ( 
        float bpnn_sim_single_ax[3]<=={0.991998,0.919734,0.859287} and skip;
        float bpnn_sim_single_a0 <== 0.991998 and skip;
        float bpnn_sim_single_a1 <== 0.919734 and skip;
        float bpnn_sim_single_a2 <== 0.859287 and skip;	 
        float bpnn_sim_single_by[1]<=={0.923673} and skip;

        int break$<==0 and skip;
        while( break$=0 AND (bpnn_sim_single_Ek_out>aveEk) )
        {
            // output(bpnn_sim_single_Ek_out, "\n") and skip;
        
            int bpnn_sim_single_1_h<==0 and skip;
            while( (bpnn_sim_single_1_h<5) )
            {
                float bpnn_sim_single_1_alpha_h<==0 and skip;
                int bpnn_sim_single_1_i<==0 and skip;

                while( (bpnn_sim_single_1_i<3) )
                {
                    bpnn_sim_single_1_alpha_h:=bpnn_sim_single_1_alpha_h+v[bpnn_sim_single_1_i,bpnn_sim_single_1_h]*bpnn_sim_single_ax[bpnn_sim_single_1_i];
                    bpnn_sim_single_1_i:=bpnn_sim_single_1_i+1

                };
                b[bpnn_sim_single_1_h]:=(1/ (1+exp(-(bpnn_sim_single_1_alpha_h-r[bpnn_sim_single_1_h]))));
                bpnn_sim_single_1_h:=bpnn_sim_single_1_h+1
            };
            
            int bpnn_sim_single_1_j<==0 and skip;

            while( (bpnn_sim_single_1_j<1) )
            {
                float bpnn_sim_single_1_beta_j<==0 and skip;
                int bpnn_sim_single_1_h_1<==0 and skip;

                while( (bpnn_sim_single_1_h_1<5) )
                {
                    bpnn_sim_single_1_beta_j:=bpnn_sim_single_1_beta_j+w[bpnn_sim_single_1_h_1,bpnn_sim_single_1_j]*b[bpnn_sim_single_1_h_1];
                    bpnn_sim_single_1_h_1:=bpnn_sim_single_1_h_1+1

                };
                yc[bpnn_sim_single_1_j]:=(1/ (1+exp(-(bpnn_sim_single_1_beta_j-o[bpnn_sim_single_1_j]))));
                bpnn_sim_single_1_j:=bpnn_sim_single_1_j+1

            };
            
            Ek:=0;
            int bpnn_sim_single_1_j_1<==0 and skip;
            while( (bpnn_sim_single_1_j_1<1) )
            {
                Ek:=Ek+(yc[bpnn_sim_single_1_j_1]-bpnn_sim_single_by[bpnn_sim_single_1_j_1])*(yc[bpnn_sim_single_1_j_1]-bpnn_sim_single_by[bpnn_sim_single_1_j_1]);
                bpnn_sim_single_1_j_1:=bpnn_sim_single_1_j_1+1

            };
            bpnn_sim_single_Ek_out:=0.5*Ek;
            int bpnn_sim_single_1_j_2<==0 and skip;

            while( (bpnn_sim_single_1_j_2<1) )
            {
                g[bpnn_sim_single_1_j_2]:=yc[bpnn_sim_single_1_j_2]*(1-yc[bpnn_sim_single_1_j_2])*(bpnn_sim_single_by[bpnn_sim_single_1_j_2]-yc[bpnn_sim_single_1_j_2]);
                bpnn_sim_single_1_j_2:=bpnn_sim_single_1_j_2+1

            };
            
            int bpnn_sim_single_1_h_2<==0 and skip;
            while( (bpnn_sim_single_1_h_2<5) )
            {
                float bpnn_sim_single_1_temp<==0 and skip;
                int bpnn_sim_single_1_j_3<==0 and skip;

                while( (bpnn_sim_single_1_j_3<1) )
                {
                    bpnn_sim_single_1_temp:=bpnn_sim_single_1_temp+w[bpnn_sim_single_1_h_2,bpnn_sim_single_1_j_3]*g[bpnn_sim_single_1_j_3];
                    bpnn_sim_single_1_j_3:=bpnn_sim_single_1_j_3+1

                };
                e[bpnn_sim_single_1_h_2]:=b[bpnn_sim_single_1_h_2]*(1-b[bpnn_sim_single_1_h_2])*bpnn_sim_single_1_temp;
                bpnn_sim_single_1_h_2:=bpnn_sim_single_1_h_2+1

            };
            
            int bpnn_sim_single_1_i_1<==0 and skip;
            while( (bpnn_sim_single_1_i_1<3) )
            {
                float bpnn_sim_single_1_temp1<==0 and skip;
                int bpnn_sim_single_1_h_3<==0 and skip;

                while( (bpnn_sim_single_1_h_3<5) )
                {
                    bpnn_sim_single_1_temp1:=bpnn_sim_single_1_temp1+v[bpnn_sim_single_1_i_1,bpnn_sim_single_1_h_3]*e[bpnn_sim_single_1_h_3];
                    bpnn_sim_single_1_h_3:=bpnn_sim_single_1_h_3+1

                };
                f[bpnn_sim_single_1_i_1]:=bpnn_sim_single_1_temp1;
                bpnn_sim_single_1_i_1:=bpnn_sim_single_1_i_1+1

            };
            
            int bpnn_sim_single_1_i_2<==0 and skip;
            while( (bpnn_sim_single_1_i_2<3) )
            {
                // output(f[bpnn_sim_single_1_i_2], "\n") and skip;
                
                if(f[bpnn_sim_single_1_i_2]>=0) then 
                {
                    bpnn_sim_single_ax[bpnn_sim_single_1_i_2]:=bpnn_sim_single_ax[bpnn_sim_single_1_i_2] + 0.000001
                }
                else 
                {
                    skip 
                };
                if(f[bpnn_sim_single_1_i_2]<0) then 
                {
                    bpnn_sim_single_ax[bpnn_sim_single_1_i_2]:=bpnn_sim_single_ax[bpnn_sim_single_1_i_2] - 0.000001
                }
                else 
                {
                    skip 
                };
                bpnn_sim_single_1_i_2:=bpnn_sim_single_1_i_2+1

            };
            bpnn_sim_single_iter:=bpnn_sim_single_iter+1
        };
         
         int bpnn_sim_single_check_attack<==0 and skip;
         if(bpnn_sim_single_Ek_out<=aveEk AND bpnn_sim_single_Ek_>aveEk) then 
         {
             bpnn_sim_single_check_attack:=1
         }
         else 
         {
              skip 
         };
         l2 := (bpnn_sim_single_a0 - bpnn_sim_single_ax[0]) * (bpnn_sim_single_a0 - bpnn_sim_single_ax[0])
                + (bpnn_sim_single_a1 - bpnn_sim_single_ax[1]) * (bpnn_sim_single_a1 - bpnn_sim_single_ax[1])
                + (bpnn_sim_single_a2 - bpnn_sim_single_ax[2]) * (bpnn_sim_single_a2 - bpnn_sim_single_ax[2]);
         l2 := sqrt(l2);
         output ("check_attack: ",bpnn_sim_single_check_attack,"\n") and skip

         // output ("\n") and skip;
         // output ("bpnn_sim_single_iter: ", bpnn_sim_single_iter, "\n") and skip;
         // output ("bpnn_sim_single_Ek_: ", bpnn_sim_single_Ek_, "\n") and skip;
         // output("bpnn_sim_single_Ek_out: ", bpnn_sim_single_Ek_out, "\n") and skip;
         // output ("Ek: ", Ek, "\n") and skip;
         // output ("aveEk: ", aveEk, "\n") and skip;
         // output ("l2: ", l2) and skip
     )
 }; 
  function main ( int  RValue )
 {
     frame(main_1_temp$_1,return) and (
     int return<==0 and skip;
     int main_1_temp$_1 and skip;
     main_1_temp$_1:=read_parameter(RValue);
     if(!main_1_temp$_1) then 
     {
         output ("Read param is failed in ","bpnn_param.txt","!\n") and skip;
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         bpnn_sim_single();
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
 };
  main(RValue)
 )
