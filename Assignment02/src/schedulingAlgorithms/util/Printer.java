package schedulingAlgorithms.util;
import schedulingAlgorithms.Task;
import java.util.ArrayList;
import java.util.List;

public class Printer {
	
	/**
	 * Prints out the statistics for all completed tasks
	 */
	public static void completedTasks(String name, List<Task> scheduledTasks, int run) {
        System.out.println("\n########################################################################################");
        System.out.println("The following processes were completed for "+name+" run " + run);
        System.out.println("########################################################################################");
        while(!scheduledTasks.isEmpty()) 
        {
            Task t = scheduledTasks.remove(0);
            System.out.println(t);
        }
	}
	
	/**
	 * 
	 * @param tasksChart
	 * @param run
	 */
	public static void timeChart(String name, ArrayList<Task> tasksChart, int run) {
        System.out.println("\n############################################################");
        System.out.println(name+" Time Chart for run " + run);
        System.out.println("############################################################");
        new GanttChart(tasksChart);
    }

	/**
	 * Prints out all calculated averages and throughput for
	 *     a completed FirstComeFirstServe simulation.
	 */	
	public static void finalBenchmark(String name, float avgTurnaroundTime, float avgWaitTime, float avgResponseTime, float throughput) {
        System.out.println("\n#######################################################################################");
        System.out.println("Final calculated averages and calculated throughput for "+name);
        System.out.println("#######################################################################################");
        System.out.println("Average Turnaround Time = " + avgWaitTime);
        System.out.println("Average Wait Time = " + avgWaitTime);
        System.out.println("Average Response Time = " + avgResponseTime);
        System.out.println("Throughput = " + throughput);
        System.out.println();
	}
}
