package submit;

import java.util.ArrayList;
import java.util.List;
import joeq.Interpreter.QuadInterpreter;
import joeq.Main.Driver;

public class OptimizeHarness {
    /*
     * args consists of
     * 1) class names that should be optimized
     * 2) a class that contains exactly one static main method, and
     * 3) a list of parameters to be pass to the main method.
     *
     * For example,
     *
     * java Optimize.main --optimize TowersOfHanoi --run-main TowersOfHanoi --run-param 3
     *
     * will optimize the class TowersOfHanoi and then interpret "java TowersOfHanoi 3"
     * using the CodeCache'd cfgs.
     *
     *
     * ATTN: DO NOT MODIFY THIS METHOD
     */
    public static void main(String[] args) {
        List<String> optimizeFiles = new ArrayList<String>();
        List<String> runMainParams = new ArrayList<String>();
        String runMainClass = null;
        boolean nullCheckOnly = true;

        for (int i = 0; i < args.length - 1; i++) {
            if (args[i].equals("--optimize")) {
                optimizeFiles.add(args[i + 1]);
            }

            if (args[i].equals("--run-main")) {
                runMainClass = args[i + 1];
            }

            if (args[i].equals("--run-param")) {
                runMainParams.add(args[i + 1]);
            }

            if (args[i].equals("--extra-credit")) {
                nullCheckOnly = false;
            }
        }

        Optimize.optimize(optimizeFiles, nullCheckOnly);

        if (runMainClass != null) {
            interpret(runMainClass, runMainParams);
        }
    }

    /**
     *
     * ATTN: DO NOT MODIFY THIS METHOD
     *
     */
    private static void interpret(String mainClass, List<String> params) {
        String[] args = new String[params.size() + 4];
        args[0] = "interpret";
        args[1] = mainClass + ".main";
        args[2] = "{";
        for (int i = 0; i < params.size(); i++) {
            args[i + 3] = params.get(i);
        }
        args[params.size() + 3] = "}";

        QuadInterpreter.num_quads = 0;
        QuadInterpreter.num_nullchecks = 0;

        Driver.main(args);
    }
}
