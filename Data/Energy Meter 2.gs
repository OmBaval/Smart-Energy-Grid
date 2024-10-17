function doGet(e) { 
  if (!e) {
    return ContentService.createTextOutput("Error: No parameters received.");
  }

  Logger.log(JSON.stringify(e));  // Log incoming request

  // Default response if everything is fine
  var result = 'Ok';

  // Check if parameters are undefined
  if (typeof e.parameter === 'undefined') {
    result = 'No Parameters';
  } else {
    var sheet_id = '1PvmTXLMVQUk11AAueERdwy8KGC8HRLlVnKYgHdrAvLA'; // Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    
    var newRow = sheet.getLastRow() + 1; 
    var rowData = [];
    var Curr_Date = new Date();
    
    rowData[0] = Curr_Date; // Date in column A
    var Curr_Time = Utilities.formatDate(Curr_Date, "Asia/Karachi", 'HH:mm:ss');
    rowData[1] = Curr_Time; // Time in column B
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      
      switch (param) {
        case 'voltage':
          rowData[2] = value; // Voltage in column C
          result = 'Voltage written in column C'; 
          break;
        case 'current':
          rowData[3] = value; // Current in column D
          result += ', Current written in column D'; 
          break;
        case 'power':
          rowData[4] = value; // Power in column E
          result += ', Power written in column E'; 
          break;
        case 'units':
          rowData[5] = value; // Units in column F
          result += ', Units written in column F'; 
          break;
        default:
          result = "Unsupported parameter"; 
      }
    }
    
    Logger.log(JSON.stringify(rowData));
    
    // Check if rowData length is correct
    if (rowData.length > 0) {
      var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
      newRange.setValues([rowData]);
    } else {
      result = "No valid data to write";
    }
  }

  return ContentService.createTextOutput(result);
}

// Remove quotes from string
function stripQuotes(value) {
  return value.replace(/^["']|['"]$/g, "");
}
