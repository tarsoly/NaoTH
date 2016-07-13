/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package de.naoth.rc.dialogs;

import de.naoth.rc.RobotControl;
import de.naoth.rc.core.dialog.AbstractDialog;
import de.naoth.rc.core.dialog.DialogPlugin;
import de.naoth.rc.dataformats.Sexp;
import de.naoth.rc.dataformats.SimsparkState;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.SwingUtilities;
import javax.swing.table.TableModel;
import javax.swing.text.DefaultCaret;
import net.xeoh.plugins.base.annotations.PluginImplementation;
import net.xeoh.plugins.base.annotations.injections.InjectPlugin;

/**
 *
 * @author Philipp Strobel <philippstrobel@posteo.de>
 */
public class TeamCommViewerSimspark extends AbstractDialog {

    @PluginImplementation
    public static class Plugin extends DialogPlugin<TeamCommViewerSimspark> {
        @InjectPlugin
        public static RobotControl parent;
    }//end Plugin
    
//    private final int port = 3100; // agent = 3100; monitor = 3200
    private final int port_agent = 3100;
    private final int port_monitor = 3200;
    
    private final String host = "127.0.0.1";
    private Simspark simspark_comm;
    private final SimsparkState sim_state = new SimsparkState();
    
    /**
     * Creates new form TeamCommViewerSimspark
     */
    public TeamCommViewerSimspark() {
        initComponents();
        DefaultCaret caret = (DefaultCaret) jTextArea1.getCaret();
        caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
        addTableContent();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jTextField1 = new javax.swing.JTextField();
        btnSendCommand = new javax.swing.JButton();
        btnConnect = new javax.swing.JToggleButton();
        jTabbedPane1 = new javax.swing.JTabbedPane();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTextArea1 = new javax.swing.JTextArea();
        jScrollPane2 = new javax.swing.JScrollPane();
        jTable1 = new javax.swing.JTable();

        btnSendCommand.setText("Send Command");
        btnSendCommand.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSendCommandActionPerformed(evt);
            }
        });

        btnConnect.setText("Connect");
        btnConnect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnConnectActionPerformed(evt);
            }
        });

        jScrollPane1.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

        jTextArea1.setColumns(20);
        jTextArea1.setRows(5);
        jScrollPane1.setViewportView(jTextArea1);

        jTabbedPane1.addTab("MonitorComm", jScrollPane1);

        jTable1.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null},
                {null, null}
            },
            new String [] {
                "Name", "Data"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        jScrollPane2.setViewportView(jTable1);

        jTabbedPane1.addTab("MonitorInfo", jScrollPane2);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(btnConnect)
                .addGap(24, 24, 24)
                .addComponent(jTextField1)
                .addGap(18, 18, 18)
                .addComponent(btnSendCommand, javax.swing.GroupLayout.PREFERRED_SIZE, 143, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
            .addComponent(jTabbedPane1)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jTextField1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnConnect)
                    .addComponent(btnSendCommand))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jTabbedPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 269, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void btnSendCommandActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSendCommandActionPerformed
        if(!jTextField1.getText().isEmpty() && simspark_comm != null && simspark_comm.isAlive()) {
            simspark_comm.sendAgentMessage(jTextField1.getText().trim());
        }
    }//GEN-LAST:event_btnSendCommandActionPerformed

    private void btnConnectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnConnectActionPerformed
        if (btnConnect.isSelected()) {
            try {
                System.out.println("...");
                
                if (simspark_comm != null) {
                    simspark_comm.disconnect();
                    simspark_comm.join();
                }
                
//                simspark_comm = new SimsparkAgent();
//                simspark_comm.connect(host, port_agent);
                simspark_comm = new SimsparkMonitor();
                simspark_comm.connect(host, port_monitor);
                simspark_comm.start();
                
            } catch (IOException | InterruptedException ex) {
                Logger.getLogger(TeamCommViewerSimspark.class.getName()).log(Level.SEVERE, null, ex);
            }
        } else {
            if (simspark_comm != null) {
                try {
                    simspark_comm.disconnect();
                    simspark_comm.join();
                } catch (InterruptedException | IOException ex) {
                    Logger.getLogger(TeamCommViewerSimspark.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            simspark_comm = null;
        }
    }//GEN-LAST:event_btnConnectActionPerformed

    private void addTableContent() {
        TableModel model = jTable1.getModel();
        model.setValueAt("time",        0, 0);
        model.setValueAt("play_mode",   1, 0);
        model.setValueAt("score_left",  2, 0);
        model.setValueAt("score_right", 3, 0);
        model.setValueAt("half",        4, 0);
        model.setValueAt("FieldLength", 5, 0);
        model.setValueAt("FieldWidth",  6, 0);
        model.setValueAt("FieldHeight", 7, 0);
        model.setValueAt("GoalWidth",   8, 0);
        model.setValueAt("GoalDepth",   9, 0);
        model.setValueAt("GoalHeight", 10, 0);
        model.setValueAt("BorderSize", 11, 0);
        model.setValueAt("FreeKickDistance", 12, 0);
        model.setValueAt("WaitBeforeKickOff",13, 0);
        model.setValueAt("AgentRadius",14, 0);
        model.setValueAt("BallRadius", 15, 0);
        model.setValueAt("BallMass",   16, 0);
        model.setValueAt("RuleGoalPauseTime",17, 0);
        model.setValueAt("RuleKickInPauseTime", 18, 0);
        model.setValueAt("RuleHalfTime",     19, 0);
        model.setValueAt("play_modes",       20, 0);
    }
    
    private class Simspark extends Thread {
        protected DataInputStream in;
        protected DataOutputStream out;
        protected Socket socket;
        protected boolean isRunning;
        
        public Simspark() {
        }
        
        public void connect(String host, int port) throws IOException {
            socket = new Socket(host, port);
//            this.socket.setTcpNoDelay(true);

            in = new DataInputStream(socket.getInputStream());
            out = new DataOutputStream(socket.getOutputStream());

            isRunning = true;
        }
        
        public void disconnect() throws IOException {
            isRunning = false;
            in.close();
            out.close();
            socket.close();
        }

        /**
         * Sends an agent message to the server.
         * <p/>
         * This method formats an agent message (String of SimSpark effector
         * messages) according to the network protocol and sends it to the
         * server.
         * <p/>
         * The content of the agent message is not validated.
         *
         * @param msg Agent message with effector commands.
         * @param out
         */
        public void sendAgentMessage(String msg) {

            byte[] body = msg.getBytes();

            //comments by the authors of magma from Offenburg:
            // FIXME: this is to compensate a server bug that clients responding too
            // quickly get problems
            // long runtime = 0;
            // boolean slowedDown = false;
            // long slowDownTime = 0;
            // int minWaitTime = 1000000;
            // do {
            // runtime = System.nanoTime() - startTime;
            // if (runtime < minWaitTime && !slowedDown) {
            // slowDownTime = minWaitTime - runtime;
            // slowedDown = true;
            // }
            // } while (runtime < minWaitTime);
            // if (slowedDown) {
            // logger.log(Level.FINE, "slowedDown sending message by: {0}",
            // slowDownTime);
            // }
            // Header of the message, specifies the length of the message:
            // "The length prefix is a 32 bit unsigned integer in network order, i.e. big 
            // endian notation with the most significant bits transferred first." 
            // (cited from 
            // http://simspark.sourceforge.net/wiki/index.php/Network_Protocol, 14.1.2012)
            int len = body.length;
            int byte0 = (len >> 24) & 0xFF;
            int byte1 = (len >> 16) & 0xFF;
            int byte2 = (len >> 8) & 0xFF;
            int byte3 = len & 0xFF;

            try {
                out.writeByte((byte) byte0);
                out.writeByte((byte) byte1);
                out.writeByte((byte) byte2);
                out.writeByte((byte) byte3);
                out.write(body);
                out.flush();
            } catch (IOException e) {
                System.out.println("Error writing to socket. Has the server been shut down?");
            }
            if(msg != "(syn)") {
                System.out.println("sended msg: "+msg);
            }
        }

        /**
         * Receives a server message and returns it.
         * <p/>
         * This method listens (blocking) for the next SimSpark message from the
         * server, removes the header concerning the SimSpark network protocol
         * and returns the server message (String of perceptor messages). <br>
         * If the server has sent more then one message since the last call of
         * this method, the oldest is returned, that means the messages are
         * provided always in chronological order.
         * <p/>
         * @param in
         * @return The raw server message (String of concatenated perceptor
         * messages).
         */
        public String getServerMessage() {
            String msg = "keine Nachricht";
            byte[] result;
            int length;

            try {
                if(in.available() == 0) { return null; }
                int byte0 = in.read();
                int byte1 = in.read();
                int byte2 = in.read();
                int byte3 = in.read();
                length = byte0 << 24 | byte1 << 16 | byte2 << 8 | byte3; // analyzes
                // the header
                int total = 0;

                if (length < 0) {
                    // server was shutdown
                    System.out.println("Server ist down.");
                }

                result = new byte[length];
                while (total < length) {
                    total += in.read(result, total, length - total);
                }
                msg = new String(result, 0, length, "UTF-8");
            } catch (IOException e) {
                System.out.println("Error when reading from socket. Has the server been shut down?");
                return null;
            }
            return msg;
        }
    }
    
    private class SimsparkAgent extends Simspark {
        public void run() {
            if(socket == null) { return; }
            // use another rsg... ?
            sendAgentMessage("(scene rsg/agent/nao/nao.rsg 0)(syn)");
            System.out.println(getServerMessage());
            sendAgentMessage("(init (unum 0)(teamname NaoTH))(syn)");
            System.out.println(getServerMessage());
            
            
            System.out.println("listening");
            
            while(isRunning) {
                try {
                    sleep(1);
                    
//                    System.out.println("next ...");
                    sendAgentMessage("(syn)");
                    String msg = getServerMessage();
                    if (msg != null) {
                        jTextArea1.append(msg + "\n");
//                        jScrollPane1.
//                        System.out.println(msg);
                    }
                } catch (InterruptedException ex) {
                    Logger.getLogger(TeamCommViewerSimspark.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }
    
    private class SimsparkMonitor extends Simspark {

        public void run() {
            if(socket == null) { return; }
            
            while(isRunning) {
                try {
                    sleep(1);
                    final String msg = getServerMessage();
                    if (msg != null) {
                        SwingUtilities.invokeLater(new Runnable() {
                            @Override
                            public void run() {
                                Sexp parser = new Sexp(msg);
                                List<Object> attributes = parser.parseSexp();
                                updateInfo(attributes);
                                updateTable();
                                jTextArea1.append(msg + "\n");
                            }
                            
                            public void updateInfo(List<Object> info) {
                                if(!info.isEmpty()) {
                                    Object o = info.get(0);
                                    if(o instanceof String) {
                                        sim_state.set((String)o, info.size() == 1?true:(info.size()==2?info.get(1):info.subList(1, info.size())));
                                    } else {
                                        for (Object object : info) {
                                            updateInfo((List<Object>) object);
                                        }
                                    }
                                }
                            }
                            
                            public void updateTable() {
                                TableModel model = jTable1.getModel();
                                for (int i = 0; i < model.getRowCount(); i++) {
                                    model.setValueAt(sim_state.get(model.getValueAt(i, 0)), i, 1);
                                }
                            }
                        });
                    }
                } catch (InterruptedException ex) {
                    Logger.getLogger(TeamCommViewerSimspark.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }
    

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToggleButton btnConnect;
    private javax.swing.JButton btnSendCommand;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JTabbedPane jTabbedPane1;
    private javax.swing.JTable jTable1;
    private javax.swing.JTextArea jTextArea1;
    private javax.swing.JTextField jTextField1;
    // End of variables declaration//GEN-END:variables
}
