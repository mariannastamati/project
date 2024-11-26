## K23α - Ανάπτυξη Λογισμικού Για Πληροφοριακά Συστήματα

### Part 1 - Αναζήτηση εγγύτερου γείτονα (Nearest Neighbor Search)
To compile: ```make```  
To run: ```make run```   
To run using valgrind: ```make val```  
To clean all: ```make clean```  

To compile using Test Main: ```make test=yes```   
To run with Test Main: ```make test=yes run```  
To run Test Main using valgrind: ```make test=yes val```   
To clean Test Main all: ```make test=yes clean```   
   
Κατασκευή ευρετηρίου-γράφου Vamana, υλοποίηση αλγορίθμων GreedySearch και RobustPrune, εύρεση του medoid με αλγόριθμο brute force.

### Part 2 - Προσεγγιστική Αναζήτηση Εγγύτερων Γειτόνων με Φίλτρα - Filtered ANNS

To compile: ```make```  

To run using default arguments: ```make run```  
To run and save output: ```make save```  
To run using custom arguments: ```make run ARGS="../dataset.bin ../queries.bin <a> <t> <L> <R> <k> <L_smal> <R_small> <R_stitched>"```  
To run and save output using custom arguments: ```make save ARGS="../dataset.bin ../queries.bin <a> <t> <L> <R> <k> <L_smal> <R_small> <R_stitched>"```   

To run using Valgrind: ```make val```  
To clean all: ```make clean```  

To compile using Test Main: ```make test=yes```    
To run with Test Main: ```make test=yes run```  
To run Test Main using valgrind: ```make test=yes val```   
To clean Test Main all: ```make test=yes clean```     


Κατασκευή ευρετηρίου γράφου με δύο τρόπους Filtered Vamana και Stitched Vamana, υλοποίηση αλγορίθμων FilteredGreedySearch και FilteredRobustPrune, 
εύρεση start node (medoid για κάθε φίλτρο) με την χρήση του αλγορίθμου FindMedoid.  
Χρησιμοποιούνται datasets που έχουν μόνο ένα φίλτρο σε κάθε στοιχείο-κόμβο
(τα datasets, πριν χρησιμοποιηθούν, "καθαρίζονται" και αφαιρούνται τα timestamps και τα queries που περιέχουν ερωτήματα που αφορούν timestamps).



**AUTHORS**  
[Χριστίνα Διαμαντή](https://github.com/ChristinaDiam) - 1115201800046  
[Μαριάννα Σταμάτη](https://github.com/mariannastamati) - 1115202000183  
[Αντρέας Γιέβτοβιτς](https://github.com/zodicx) - 1115202000033

