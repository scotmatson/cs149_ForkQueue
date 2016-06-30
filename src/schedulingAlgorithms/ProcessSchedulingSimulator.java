package schedulingAlgorithms;
import java.util.*;
/**
 *COPYRIGHT (C) 2016 CS149_1 Group forkQueue. All Rights Reserved.
 * The process scheduling simulator uses various algorithms to
 * simulate process scheduling
 * Solves CS149 Homework#2
 * @author Tyler Jones, Scot Matson, ______....
 */
public class ProcessSchedulingSimulator {
    //Declare all final variables
    private final static int QUANTA_MAX = 100;
    private final static int RUNTIME_MAX = 10;
    private final static int PRIORITY_MAX = 4;
    private final static int NUM_OF_TASKS = 1000;

    /**
     * The main method. The entry point for the application.
     * 
     * @param args (String Array) : User-defined arguments.
     */
    public static void main(String[] args) {
        ProcessSchedulingSimulator pss = new ProcessSchedulingSimulator();
        Scanner input = new Scanner(System.in);
        int option = 1;
        while(option >= 1 && option <= 7) {
            pss.printMenuOptions();
            option = input.nextInt();
            ProcessQueue processQueue = new ProcessQueue(QUANTA_MAX, RUNTIME_MAX, PRIORITY_MAX, NUM_OF_TASKS);
            switch(option) 
            {
                case 1:
                	new FirstComeFirstServe(processQueue).runNonPreemptive();
                	break;
                case 2:
                	new ShortestJobFirst(processQueue).runNonPreemptive();
                	break;
                case 3:
                	new ShortestRemainingTime(processQueue).runPreemptive();
                	break;
                case 4:
                    new RoundRobin(processQueue).runPreemptive();
                	break;
                case 5:
                	new HighestPriorityFirst(processQueue).runNonPreemptive();
                	break;
                case 6:
                	new HighestPriorityFirst_preemptive(processQueue).runPreemptive();
                	break;
                case 7:
                    new HPFP_Aging(processQueue).runHPFP_Aging();
                    break;
                default: 
                	option = 8;
                	break;
            }
        }
        input.close();
    }
    
    /**
     * A helper method which prints out a console-based
     * user-interface.
     */
    private void printMenuOptions()
    {
    	System.out.println(
    			"Please choose the number of the " +
                "process scheduling algorithm you would like to run:\n" +
                "(1) First Come First Served\n" + 
                "(2) Shortest Job First\n" +
                "(3) Shortest Remaining Time\n" +
                "(4) Round Robin\n" +
                "(5) Highest Priority First (non-preemptive)\n" +
                "(6) Highest Priority First (Preemptive)" + "\n" + "(7) HPF_Aging(Preemptive)\n" + "(8) Exit"
    	);	
    }
}
