package schedulingAlgorithms;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

import schedulingAlgorithms.util.Printer;

public class HighestPriorityFirst_nonpreemptive_aging {
	private final String name = "Aging HPF-NP";
    private ProcessQueue processQueue;
    private int finalTasksDone;
    private int finalTasksDoneP1;
    private int finalTasksDoneP2;
    private int finalTasksDoneP3;
    private int finalTasksDoneP4;
    private float finalTurnaroundTime;
    private float finalTurnaroundTimeP1;
    private float finalTurnaroundTimeP2;
    private float finalTurnaroundTimeP3;
    private float finalTurnaroundTimeP4;
    private float finalWaitTime;
    private float finalWaitTimeP1;
    private float finalWaitTimeP2;
    private float finalWaitTimeP3;
    private float finalWaitTimeP4;
    private float finalResponseTime;
    private float finalResponseTimeP1;
    private float finalResponseTimeP2;
    private float finalResponseTimeP3;
    private float finalResponseTimeP4;
    private float finalTime;
    
    public HighestPriorityFirst_nonpreemptive_aging(ProcessQueue processQueue)
    {
        this.processQueue = processQueue;
        this.finalTasksDone = 0;
        this.finalTasksDoneP1 = 0;
        this.finalTasksDoneP2 = 0;
        this.finalTasksDoneP3 = 0;
        this.finalTasksDoneP4 = 0;
        this.finalTurnaroundTime = 0.0f;
        this.finalTurnaroundTimeP1 = 0.0f;
        this.finalTurnaroundTimeP2 = 0.0f;
        this.finalTurnaroundTimeP3 = 0.0f;
        this.finalTurnaroundTimeP4 = 0.0f;
        this.finalWaitTime = 0.0f;
        this.finalWaitTimeP1 = 0.0f;
        this.finalWaitTimeP2 = 0.0f;
        this.finalWaitTimeP3 = 0.0f;
        this.finalWaitTimeP4 = 0.0f;
        this.finalResponseTime = 0.0f;
        this.finalResponseTimeP1 = 0.0f;
        this.finalResponseTimeP2 = 0.0f;
        this.finalResponseTimeP3 = 0.0f;
        this.finalResponseTimeP4 = 0.0f;
        this.finalTime = 0.0f;
    }


    /**
     * Highest Priority First (non-preemptive) with aging
     */
    public void runNonPreemptive() {
        for(int i = 1; i <= 5; i++) 
        {
            // Variables needed for tracking progress of each run
            int clock = 0;
            int tasksDone = 0;
            int tasksDoneP1 = 0;
            int tasksDoneP2 = 0;
            int tasksDoneP3 = 0;
            int tasksDoneP4 = 0;
            int totalTasksDone = 0;
            int totalTasksDoneP1 = 0;
            int totalTasksDoneP2 = 0;
            int totalTasksDoneP3 = 0;
            int totalTasksDoneP4 = 0;
            float completionTime = 0.0f;
            float totalTime = 0.0f;
            float totalTurnaroundTime = 0.0f;
            float totalTurnaroundTimeP1 = 0.0f;
            float totalTurnaroundTimeP2 = 0.0f;
            float totalTurnaroundTimeP3 = 0.0f;
            float totalTurnaroundTimeP4 = 0.0f;
            float totalWaitTime = 0.0f;
            float totalWaitTimeP1 = 0.0f;
            float totalWaitTimeP2 = 0.0f;
            float totalWaitTimeP3 = 0.0f;
            float totalWaitTimeP4 = 0.0f;
            float totalResponseTime = 0.0f;
            float totalResponseTimeP1 = 0.0f;
            float totalResponseTimeP2 = 0.0f;
            float totalResponseTimeP3 = 0.0f;
            float totalResponseTimeP4 = 0.0f;
            ArrayList<Task> scheduledTasks = new ArrayList<>();
            ArrayList<Task> scheduledTasksP1 = new ArrayList<>();
            ArrayList<Task> scheduledTasksP2 = new ArrayList<>();
            ArrayList<Task> scheduledTasksP3 = new ArrayList<>();
            ArrayList<Task> scheduledTasksP4 = new ArrayList<>();

            // For each of 5 runs create a new process queue
            Task[] tasks = processQueue.generateProcesses(i);

            // Place task list into a queue for easier processing with HPF-NP
            Queue<Task> taskList = new LinkedList<Task>(Arrays.asList(tasks));
            
            // Comparator for the 4 priority queues.
            // Priority by arrival time with ties broken by run time
            Comparator<Task> c = new Comparator<Task>() {
                public int compare(Task t1, Task t2)
                {
                    int difference = t1.compareArrivalTime(t2.getArrivalTime());
                    if (difference == 0)
                    {
                        return (t1.compareRunTime(t2.getRunTime()));
                    }
                    return difference;
                }
            };
            // Create 4 Queues, one for each priority
            PriorityQueue<Task> readyQueueP1 = new PriorityQueue<>(10, c);
            PriorityQueue<Task> readyQueueP2 = new PriorityQueue<>(10, c);
            PriorityQueue<Task> readyQueueP3 = new PriorityQueue<>(10, c);
            PriorityQueue<Task> readyQueueP4 = new PriorityQueue<>(10, c);

            // Run the algorithm for all tasks
            while (!taskList.isEmpty() || !readyQueueP1.isEmpty() || !readyQueueP2.isEmpty()
                    || !readyQueueP3.isEmpty() || !readyQueueP4.isEmpty()) 
            {
                // Get the correct process to be scheduled based on priority
                // Tasks in readyQueue's have arrived by this time
                Task t;
                if (!readyQueueP1.isEmpty()) 
                {
                    t = readyQueueP1.poll();
                }
                else if (!readyQueueP2.isEmpty()) 
                {
                    t = readyQueueP2.poll();
                }
                else if (!readyQueueP3.isEmpty()) 
                {
                    t = readyQueueP3.poll();
                }
                else if (!readyQueueP4.isEmpty()) 
                {
                    t = readyQueueP4.poll();
                }
                else 
                {
                    //No tasks have arrived yet so get the next task that has
                    t = taskList.poll();
                }

                //Update start and completion times for this process
                int startTime = Math.max((int)Math.ceil(t.getArrivalTime()), clock);
                if (startTime > 99) break;
                t.setStartTime(startTime);
                completionTime = startTime + t.getRunTime();
                t.setCompletionTime(completionTime);

                
                // Check the age of each priority queue to see if its been waiting for more than 5 quanta
                int waitP2 = 0;
                int waitP3 = 0;
                int waitP4 = 0;
                do
                {
                    // Only get waitTimes from queues that have processes in them otherwise keep waitTime at 0
                    waitP2 = (readyQueueP2.peek() != null) ? (startTime - readyQueueP2.peek().getArrivalTime()) : 0;
                    waitP3 = (readyQueueP3.peek() != null) ? (startTime - readyQueueP3.peek().getArrivalTime()) : 0;
                    waitP4 = (readyQueueP4.peek() != null) ? (startTime - readyQueueP4.peek().getArrivalTime()) : 0;

                    // Upgrade any tasks with waitTimes of more than 5 quanta
                    if (waitP2 >= 5)
                    {
                        readyQueueP1.add(readyQueueP2.poll());
                    }
                    if (waitP3 >= 5)
                    {
                        readyQueueP2.add(readyQueueP3.poll());
                    }
                    
                    if (waitP4 >= 5)
                    {
                        readyQueueP3.add(readyQueueP4.poll());
                    }
                }
                while (waitP2 >= 5 || waitP3 >= 5 || waitP3 >= 5);// End do/while loop

                // Add in the correct ArrayList for completed tasks
                int thisP = t.getPriority();
                switch (thisP)
                {
                    case 1:
                        scheduledTasksP1.add(t);
                        tasksDoneP1++;
                        break;
                    case 2:
                        scheduledTasksP2.add(t);
                        tasksDoneP2++;
                        break;
                    case 3:
                        scheduledTasksP3.add(t);
                        tasksDoneP3++;
                        break;
                    default:
                        scheduledTasksP4.add(t);
                        tasksDoneP4++;
                        break;
                }
                
                // Update all completed tasks and clock
                scheduledTasks.add(t);
                tasksDone++;
                clock = (int)Math.ceil(completionTime);

                // Add processes to the ready queue that have arrived by this time
                while (taskList.peek() != null && taskList.peek().getArrivalTime() <= clock) 
                {
                    Task next = taskList.poll();
                    
                    int nextP = next.getPriority();
                    switch (nextP)
                    {
                        case 1:
                            readyQueueP1.add(next);
                            break;
                        case 2:
                            readyQueueP2.add(next);
                            break;
                        case 3:
                            readyQueueP3.add(next);
                            break;
                        default:
                            readyQueueP4.add(next);
                            break;
                    }
                }

                // Variables for statistics for this process only
                float turnaroundTime = (completionTime - t.getArrivalTime());
                float waitTime = (turnaroundTime - t.getRunTime());
                int responseTime = (startTime - t.getArrivalTime());

                // Update totals at end of each run for each priority queue
                switch (thisP)
                {
                    case 1:
                        totalTurnaroundTimeP1 += turnaroundTime;
                        totalWaitTimeP1 += waitTime;
                        totalResponseTimeP1 += responseTime;
                        totalTasksDoneP1 = tasksDoneP1;
                        break;
                    case 2:
                        totalTurnaroundTimeP2 += turnaroundTime;
                        totalWaitTimeP2 += waitTime;
                        totalResponseTimeP2 += responseTime;
                        totalTasksDoneP2 = tasksDoneP2;
                        break;
                    case 3:
                        totalTurnaroundTimeP3 += turnaroundTime;
                        totalWaitTimeP3 += waitTime;
                        totalResponseTimeP3 += responseTime;
                        totalTasksDoneP3 = tasksDoneP3;
                        break;
                    default:
                        totalTurnaroundTimeP4 += turnaroundTime;
                        totalWaitTimeP4 += waitTime;
                        totalResponseTimeP4 += responseTime;
                        totalTasksDoneP4 = tasksDoneP4;
                        break;
                }
                
                // Update totals at end of each run for all processes
                totalTurnaroundTime += turnaroundTime;
                totalWaitTime += waitTime;
                totalResponseTime += responseTime;
                totalTasksDone = tasksDone;
                
                if (completionTime >= 99) 
                {
                    totalTime = completionTime; //time until last process is complete
                } 
                else 
                {
                    totalTime = 99;
                }
            }
            
            // Update final numbers needed for averages at each of 5 runs
            finalTurnaroundTime += totalTurnaroundTime;
            finalTurnaroundTimeP1 += totalTurnaroundTimeP1;
            finalTurnaroundTimeP2 += totalTurnaroundTimeP2;
            finalTurnaroundTimeP3 += totalTurnaroundTimeP3;
            finalTurnaroundTimeP4 += totalTurnaroundTimeP4;
            finalWaitTime += totalWaitTime;
            finalWaitTimeP1 += totalWaitTimeP1;
            finalWaitTimeP2 += totalWaitTimeP2;
            finalWaitTimeP3 += totalWaitTimeP3;
            finalWaitTimeP4 += totalWaitTimeP4;
            finalResponseTime += totalResponseTime;
            finalResponseTimeP1 += totalResponseTimeP1;
            finalResponseTimeP2 += totalResponseTimeP2;
            finalResponseTimeP3 += totalResponseTimeP3;
            finalResponseTimeP4 += totalResponseTimeP4;
            finalTasksDone += totalTasksDone;
            finalTasksDoneP1 += totalTasksDoneP1;
            finalTasksDoneP2 += totalTasksDoneP2;
            finalTasksDoneP3 += totalTasksDoneP3;
            finalTasksDoneP4 += totalTasksDoneP4;
            finalTime += totalTime;

            // Make a copy of the completed tasks to use in the time chart
            ArrayList<Task> tasksChart = new ArrayList<Task>(scheduledTasks);
            Printer.completedTasks(name, scheduledTasks, i);
            Printer.timeChart(name, tasksChart, i);
        }
        
        printFinalBenchmark();
    }
    
    /**
     * Prints out all calculated averages and throughput for
     *     a completed HighestPriorityFirst-NP simulation.
     */
    public void printFinalBenchmark()
    {
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY1 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTimeP1/finalTasksDoneP1);
        System.out.println("Average Wait Time = " + finalWaitTimeP1/finalTasksDoneP1);
        System.out.println("Average Response Time = " + finalResponseTimeP1/finalTasksDoneP1);
        System.out.println("Throughput = " + finalTasksDoneP1/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY2 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTimeP2/finalTasksDoneP2);
        System.out.println("Average Wait Time = " + finalWaitTimeP2/finalTasksDoneP2);
        System.out.println("Average Response Time = " + finalResponseTimeP2/finalTasksDoneP2);
        System.out.println("Throughput = " + finalTasksDoneP2/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY3 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTimeP3/finalTasksDoneP3);
        System.out.println("Average Wait Time = " + finalWaitTimeP3/finalTasksDoneP3);
        System.out.println("Average Response Time = " + finalResponseTimeP3/finalTasksDoneP3);
        System.out.println("Throughput = " + finalTasksDoneP3/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY4 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTimeP4/finalTasksDoneP4);
        System.out.println("Average Wait Time = " + finalWaitTimeP4/finalTasksDoneP4);
        System.out.println("Average Response Time = " + finalResponseTimeP4/finalTasksDoneP4);
        System.out.println("Throughput = " + finalTasksDoneP4/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("##### Final calculated averages and calculated throughput for HPF-NP ALL PROCESSES ######");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime/finalTasksDone);
        System.out.println("Average Wait Time = " + finalWaitTime/finalTasksDone);
        System.out.println("Average Response Time = " + finalResponseTime/finalTasksDone);
        System.out.println("Throughput = " + finalTasksDone/finalTime);
        System.out.println();
    }
}
