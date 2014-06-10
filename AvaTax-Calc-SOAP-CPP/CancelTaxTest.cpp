#include "stdafx.h"
#include "CancelTaxTest.h"

using namespace System;
using namespace Avalara::AvaTax::Adapter;
using namespace Avalara::AvaTax::Adapter::TaxService;

CancelTaxTest::CancelTaxTest(){}

void CancelTaxTest::Test()
{
	String^ accountNumber = "1234567890";
	String^ licenseKey = "A1B2C3D4E5F6G7H8";
	String^ serviceURL = "https://development.avalara.net";

	try
	{
		TaxSvc^ taxSvc = gcnew TaxSvc;

		// Header Level Parameters
		// Required Header Parameters
		taxSvc->Configuration->Security->Account = accountNumber;
		taxSvc->Configuration->Security->License = licenseKey;
		taxSvc->Configuration->Url = serviceURL;
		taxSvc->Configuration->ViaUrl = serviceURL;
		taxSvc->Profile->Client = "AvaTaxSample";

		CancelTaxRequest^ cancelTaxRequest = gcnew CancelTaxRequest;

		// Required Request Parameters
		cancelTaxRequest->CancelCode = CancelCode::DocVoided;
		cancelTaxRequest->CompanyCode = "APITrialCompany";
		cancelTaxRequest->DocType = DocumentType::SalesInvoice;
		cancelTaxRequest->DocCode = "INV001";

		CancelTaxResult^ cancelTaxResult = taxSvc->CancelTax(cancelTaxRequest);	

		Console::WriteLine("CancelTaxTest Result: {0}", cancelTaxResult->ResultCode.ToString());
		if(cancelTaxResult->ResultCode != SeverityLevel::Success)
		{
			for each (Message^ message in cancelTaxResult->Messages)
			{
				Console::WriteLine("{0}\n{1}\n{2}\n{3}",
					message->Name,
					message->Summary,
					message->RefersTo,
					message->Details);
			}
		}
		else
		{
			Console::WriteLine("Document Voided.");
		}
	}
	catch(Exception^ ex)
	{
		Console::WriteLine("Exception: {0}", ex->Message);
	}
	Console::WriteLine("----------------------------------------------");
}